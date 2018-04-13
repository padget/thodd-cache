#ifndef __thodd_iterator_iteration_hpp__
#  define __thodd_iterator_iteration_hpp__

namespace thodd {
  /** 
   * @brief  Execute une fonction on_each sur chacun des éléments accessible depuis l'iterateur
   * @param  it: iterateur exploré pour l'execution de on_each
   * @param  on_each: fonction exécutée à chaque étape
   */
  void foreach (auto const & it, auto const & on_each) {
    auto cursor = it ;
    
    while (has_next(cursor)) {
      on_each(in(cursor)) ;
      next(cursor) ;
    }
  }
}

#endif