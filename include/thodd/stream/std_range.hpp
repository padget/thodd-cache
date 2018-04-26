#ifndef __thodd_cache_stream_std_range_hpp__
#  define __thodd_cache_stream_std_range_hpp__

namespace thodd {
  /// Wrapper permettant de migrer un iterator standart vers
  /// les methodes de lazy stream
  template <typename iterator_t> 
  struct std_range_stream {
    iterator_t it ;
    iterator_t end ;
  } ;

  /** 
   * @brief  Construit un std_range_stream à partir d'un container standart.
   * @param  begin: iterateur de début
   * @param  end: iterateur de fin
   */
  template <typename iterator_t>
  std_range_stream<iterator_t> 
  make_range (iterator_t const & begin, iterator_t const & end) {
    return {begin, end} ;
  }

  /** 
   * @brief  Construit un std_range_stream à partir d'un container standart. 
   * @param  c: container standart
   */
  template <typename stdcontainer_t>
  std_range_stream<typename stdcontainer_t::const_iterator> 
  make_range (stdcontainer_t const & c) {
    return {c.begin(), c.end()} ;
  }

  /** 
   * @brief  Accessor sur le contenu courant de l'itérateur
   * @param  srit: iterateur dont on veut obtenir le contenu
   */
  auto in (std_range_stream<auto> const & srit) -> decltype(auto) {
    return *srit.it ;
  }

  /** 
   * @brief  Test si l'iterateur à un suivant
   * @param  srit: iterateur testé par la fonction
   */
  bool has_next (std_range_stream<auto> const & srit) {
    return srit.it != srit.end ;
  }

  /** 
   * @brief  Retourne le suivant d'un iterateur
   * @param  srit: iterateur dont on veut le suivant
   */
  auto next (std_range_stream<auto> & srit) -> decltype(srit) {
    srit.it = std::next(srit.it) ;
    return srit ;
  }
}

#endif