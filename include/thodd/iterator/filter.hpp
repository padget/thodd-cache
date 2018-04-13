#ifndef __thodd_cache_iterator_filter_hpp__
#  define __thodd_cache_iterator_filter_hpp__

namespace thodd {
  /// map_iterator est un iterateur permettant de wrapper 
  /// un autre iterator avec de nouvelles methodes d'accès 
  /// conditionnées par le predicate. C'est la méthode next 
  /// qui est concernée principalement. Elle avance le cursor
  /// jusqu'à ce que le predicat soit vérifié.
  template <typename iterator_t, 
            typename predicate_t>
  struct filter_iterator {
    iterator_t it ;      
    predicate_t predicate ;
  } ;

  /** 
   * @brief  Accessor sur le contenu courant de l'itérateur
   * @param  srit: iterateur dont on veut obtenir le contenu
   */
  auto in (filter_iterator<auto, auto> const & fit) -> decltype(auto) {
    return in(fit.it) ;
  } 

  /** 
   * @brief  Test si l'iterateur à un suivant
   * @param  srit: iterateur testé par la fonction
   */
  bool has_next (filter_iterator<auto, auto> const & fit) {
    return has_next(fit.it) ;
  }
   
  /** 
   * @brief  Retourne le suivant d'un iterateur
   * @param  srit: iterateur dont on veut le suivant
   * @note   L'iterateur va être testé et avancer 
   * jusqu'au premier élément validant le filtre
   */
  auto next (filter_iterator<auto, auto> & fit) -> decltype(fit) {
    while (has_next(fit.it)) {
      next(fit.it) ;
      
      if (has_next(fit.it) && fit.predicate(in(fit.it))) 
        break ;
    }

    return fit ; 
  }

  /** 
   * @brief  Construit un filter_iterator à partir d'un iterator et d'un predicat
   * @param  it: iterateur sur lequel on va appliquer le filtre
   * @param  predicate: predicat pour filtrer les éléments de l'iterateur
   */
  template <typename iterator_t,
            typename predicate_t>
  filter_iterator<iterator_t, predicate_t> 
  filter (iterator_t const & it, predicate_t const & predicate) {
    filter_iterator<iterator_t, predicate_t> fit {it, predicate} ;
    return next(fit) ;
  }

}

#endif




