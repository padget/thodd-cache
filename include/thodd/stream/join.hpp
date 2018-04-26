#ifndef __thodd_cache_stream_join_hpp__
#  define __thodd_cache_stream_join_hpp__

#  include <tuple>
#  include <thodd/stream/foreach.hpp>

// TODO Documentation à revoir
namespace thodd {
  /// join_iterator est un iterateur permettant de wrapper 
  /// deux autres iterators afin de permettre leur parcours en parallèle.
  template <typename ... iterator_t>
  struct join_iterator {
    std::tuple<iterator_t...> its ;
  } ;

  /** 
   * @brief Retourne l'objet porté par l'iterator
   * @param mit: map_iterator dont on souhaite récupérer l'objet  
   * @retval valeur portée par l'iterator
   */
  template <typename ... iterator_t>
  auto in (join_iterator<iterator_t...> const & jit) -> decltype(auto) {
    return std::apply(
      [](auto && ...its) {
        return std::forward_as_tuple(std::forward<decltype(in(its))>(in(its))...) ;
      }, 
      jit.its) ;
  }

  /** 
   * @brief Détermine si l'iterator possède un suivant.
   * @retval Retourne true si il y a un suivant, false sinon.
   */
  template <typename ... iterator_t>
  bool has_next (join_iterator<iterator_t...> const jit) {
    return std::apply([] (auto && ... its) {
      return (has_next(its) && ...) ;
    }, jit.its) ;
  }

  /** 
   * @brief Retourne le suivant de l'iterator en paramètre 
   */
  template <typename ... iterator_t>
  auto next (join_iterator<iterator_t...> & jit) -> decltype(jit) {
    jit.its = std::apply([] (auto & ... its) {return std::make_tuple(next(its)...) ;}, jit.its) ;
    return jit ;
  }

  /** 
   * @brief   Construit un join_iterator
   * @param  it1: iterateur 1 de la jointure
   * @param  it2: iterateur 2 de la jointure
   * @retval un join_iterator construit à partir de deux autres iterators
   */
  template <typename ... iterator_t>
  join_iterator<iterator_t...> 
  join (iterator_t const & ... it) {
    return {{it...}} ;
  }

  /** 
   * @brief  Fonction appliquant on_each sur un join_iterator
   * @param  jit: join_iterator sur lequel on va appliquer on_each
   * @param  on_each: fonction appliqué sur jit
   */
  template <typename ... iterator_t>
  void foreach_n (join_iterator<iterator_t...> const & jit, auto const & on_each) {
    auto cursor = jit ;

    while (has_next(cursor)) {
      std::apply([on_each=on_each] (auto const & ... values) {on_each(values...) ;}, in(cursor)) ;
      next(cursor) ;
    }
  }

  /** 
   * @brief  Applique une réduction reducer sur l'it avec pour valeur initiale de reduction init 
   * @param  it: iterator sur lequel la réduction sera appliquée
   * @param  reducer: fonction d'accumulation appliquée
   * @param  init: valeur initiale de l'accumulation
   * @retval résultat de l'accumulation sur it
   */
  template <typename ... iterator_t>
  auto reduce_n (join_iterator<iterator_t...> const & it, auto const & reducer, auto const & init) {
    auto res = init ; 
    foreach_n(it, [&res, reducer] (auto const &... values) {
      res = reducer(values..., res) ;
    }) ;

    return res ;
  }

  /** 
   * @brief Fonction appliquant une fonction de mapping sur un join_iterator  
   * @param  jit: join_iterator sur lequel on va appliquer le mapping
   * @param  mapper_n: fonction de mapping appliquée sur jit
   * @retval un iterator de mapping portant jit et mapping
   */
  template <typename ... iterator_t>
  auto map_n (join_iterator<iterator_t...> const & jit, auto const & mapper_n) {
    return map(jit, [mapper_n] (auto const & items) {
      return std::apply(mapper_n, items) ;
    }) ;
  }

  /** 
   * @brief  Fonction appliquant un filtrage sur un join_iterator
   * @param  jit: join_iterator sur lequel on va appliquer le filtrage
   * @param  predicate_n: predicat de filtrage
   * @retval un iterator de filtrage portant predicate et jit
   */
  template <typename ... iterator_t>
  auto filter_n (join_iterator<iterator_t...> const & jit, auto const & predicate_n) {
    return filter(jit, [predicate_n] (auto const & items) {
      return std::apply(predicate_n, items) ;
    }) ;
  }
}

#endif