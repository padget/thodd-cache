#ifndef __thodd_stream_fluent_hpp__
#  define __thodd_stream_fluent_hpp__

#  include <thodd/stream/stream.hpp>

namespace thodd {

  // Un stream représente le flux de donnée sur lequel on va itérer.
  // iterator_t est le type de l'iterator que porte le stream
  template <typename iterator_t>
  struct stream ;

  /** 
   * @brief  Factory permettant de construit un stream<iterator_t>
   * @param  it: iterator de parcour porté par le stream
   * @retval un stream<iterator_t> construit avec it
   */
  template <typename iterator_t>
  stream<iterator_t> make_stream (iterator_t const & it) {
    return {it} ;
  }

  /** 
   * @brief  Construit un stream à partir d'un container
   * @param  container: container dont on souhaite obtenir un stream
   * @retval stream basé sur l'iterator du container
   */
  auto as_stream(auto const & container) {
    return make_stream(thodd::make_range(container)) ;
  }
  
  // Un stream_n représente un flux de donnée sur lequel on va 
  // itérer en parallèle sur plusieurs iterators.
  template <typename ... iterator_t>
  struct stream_n ;

   /** 
   * @brief  Factory permettant de construit un stream_n<iterator_t...>
   * @param  its: iterators de parcour portés par le stream
   * @retval un stream_n<iterator_t...> construit avec its
   */
  template <typename ... iterator_t>
  stream_n<iterator_t...> make_stream_n (iterator_t const & ... its) {
    return {thodd::join(its...)} ;
  }

  // Un stream permet de faire de la programmation fluent. 
  // Cela respecte toujours les principes de la programmation 
  // fonctionnelle car chaque fonction remonte un nouveau 
  // stream ou résultat
  template <typename iterator_t>
  struct stream {
    iterator_t it ;

    /** 
     * @brief  fonction fluent permettant de créer un stream de mapping
     * @param  mapper: mapper qui sera appliqué sur it
     * @retval un nouveau stream construit avec mapper et le stream courant
     */
    auto map (auto const & mapper) {
      return make_stream(thodd::map(it, mapper)) ;
    }

    /** 
     * @brief  fonction fluent permettant de créer un stream de filtrage
     * @param  predicate: predicate de filtrage appliqué sur it
     * @retval un nouveau stream construit avec predicate et le stream courant
     */
    auto filter (auto const & predicate) {
      return make_stream(thodd::filter(it, predicate)) ;
    }

    /** 
     * @brief  fonction fluent permettant de créer un stream de collect
     * @param  collector: collector appliqué sur it
     * @retval un nouveau stream construit avec un collector et le steam courant
     */
    auto collect (auto const & collector) {
      return thodd::collect(it, collector) ;
    }

    /** 
     * @brief  fonction fluent retournant le résultat d'un reduce sur le stream courant
     * @param  reducer: reducer utilisé par la fonction reduce
     * @param  init: valeur initiale de l'accumulateur du reducer
     * @retval résultat de l'accumulation du reducer sur l'it partant de init
     */
    auto reduce (auto const & reducer, auto const & init) {
      return thodd::reduce(it, reducer, init) ;
    }

    /** 
     * @brief  fonction fluent permettant l'execution d'une fonction on_each sur it
     * @param  on_each: fonction appliqué sur les éléments d'it
     */
    void foreach (auto const & on_each) {
      thodd::foreach(it, on_each) ;
    }

    /** 
     * @brief  fonction fluent permettant la construction d'un stream_n à 
     *         partir du stream courant et des autres its
     * @param  its: autres iterator à joindre à it 
     * @retval un nouveau stream_n construit avec it et its...
     */
    auto join (auto const & ... its) {
      return make_stream_n(it, its...) ;
    }
  } ;

  //
  template <typename ... iterator_t>
  struct stream_n {
    join_iterator<iterator_t...> jit ;

    /** 
     * @brief  fonction fluent permettant de construire un stream_n de mapping
     * @param  mapper_n: mapper qui sera appliqué sur le join_iterator
     * @retval un stream_n construit à partir de mapper_n
     */
    auto map_n(auto const & mapper_n) {
      return make_stream(thodd::map_n(jit, mapper_n)) ;
    }
    
    /** 
     * @brief  fonction fluent permettant de construire un stream_n de filtrage
     * @param  predicate_n: predicate de filtrage qui sera appliqué sur le join_iterator
     * @retval un stream_n construit à partir du predicate_n
     */
    auto filter_n(auto const & predicate_n) {
      return make_stream(thodd::filter_n(jit, predicate_n)) ;
    }

    /** 
     * @brief  fonction fluent permettant d'appliquer une réduction sur le join_iterator
     * @param  reducer_n: fonction d'accumulation 
     * @param  init: valeur initiale de l'accumulation
     * @retval résultat de l'accumulation du join_iterator
     */
    auto reduce_n (auto const & reducer_n, auto const & init) {
      return thodd::reduce_n(jit, reducer_n, init) ;
    }

    /** 
     * @brief  fonction fluent permettant d'appliquer on_each sur un join_iterator
     * @param  on_each_n: fonction appliquer sur le join_iterator
     */
    void foreach_n (auto const & on_each_n) {
      thodd::foreach_n(jit, on_each_n) ;
    }
  } ;
}

#endif