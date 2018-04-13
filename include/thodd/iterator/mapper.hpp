#ifndef __thodd_cache_iterator_mapper_hpp__
#  define __thodd_cache_iterator_mapper_hpp__

namespace thodd {
  /// map_iterator est un iterateur permettant de wrapper 
  /// un autre iterator avec de nouvelles methodes d'accès 
  /// conditionnées par le mapper.
  template <typename iterator_t, 
            typename mapper_t>
  struct map_iterator {
    iterator_t it ;
    mapper_t mapper ;
  } ;

  /** 
   * @brief Retourne l'objet porté par l'iterator
   * @param mit: map_iterator dont on souhaite récupérer l'objet  
   * @retval valeur portée par l'iterator
   */
  auto in (map_iterator<auto, auto> const & mit) -> decltype(auto) {
    return mit.mapper(in(mit.it)) ;
  }

  /** 
   * @brief Détermine si l'iterator possède un suivant.
   * @retval Retourne true si il y a un suivant, false sinon.
   */
  bool has_next (map_iterator<auto, auto> const mit) {
    return has_next(mit.it) ;
  }

  /** 
   * @brief Retourne le suivant de l'iterator en paramètre 
   */
  auto next (map_iterator<auto, auto> & mit) -> decltype(mit) {
    next(mit.it) ;
    return mit ; 
  }

  /** 
   * @brief Construit un map_iterator
   * @param  it: iterator sur lequel on veut appliquer le mapper
   * @param  mapper: mapper qu'on veut appliquer sur l'iterator
   * @retval un map_iterator construit à partir d'un iterator et d'un mapper
   */
  template <typename iterator_t, 
            typename mapper_t> 
  map_iterator<iterator_t, mapper_t> 
  map (iterator_t const & it, mapper_t const & mapper) {
    return {it, mapper} ;
  }
}

#endif