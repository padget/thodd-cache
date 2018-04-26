#ifndef __thodd_stream_iteration_hpp__
#  define __thodd_stream_iteration_hpp__


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

  /** 
   * @brief  Applique une réduction reducer sur l'it avec pour valeur initiale de reduction init 
   * @param  it: iterator sur lequel la réduction sera appliquée
   * @param  reducer: fonction d'accumulation appliquée
   * @param  init: valeur initiale de l'accumulation
   * @retval résultat de l'accumulation sur it
   */
  auto reduce (auto const & it, auto const & reducer, auto const & init) {
    auto res = init ;
    foreach(it, [&res, reducer=reducer] (auto const & value) {
      res = reducer(value, res) ;
    }) ;
    return res ;
  }
}

#endif