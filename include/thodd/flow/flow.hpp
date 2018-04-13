#ifndef __thodd_flow_flow_hpp__
#  define __thodd_flow_flow_hpp__

#  include <thodd/iterator/iterator.hpp>

namespace thodd::flow {
  /** 
   * @brief  Construit une préparation de la fonction de thodd::map 
   * @param  mapper: mapper qui sera passé à la fonction thodd::map
   * @retval résultat de la fonction thodd::map avec le mapper et l'itérateur
   */
  auto map (auto const & mapper) {
    return [=] (auto const & it) {
      return thodd::map(it, mapper) ;
    } ;
  }

  /** 
   * @brief  Construit une préparation de la fonction de thodd::filter 
   * @param  predicate: predicat qui sera passé à la fonction thodd::filter
   * @retval résultat de la fonction thodd::filter avec le predicat et l'itérateur
   */
  auto filter (auto const & predicate) {
    return [=] (auto const & it) {
      return thodd::filter(it, predicate) ;
    } ;
  }

  /** 
   * @brief  Construit une préparation de la fonction de thodd::collect 
   * @param  collector: collector qui sera passé à la fonction thodd::collect
   * @retval résultat de la fonction thodd::collect avec le collector et l'itérateur
   */  
  auto collect (auto const & collector) {
    return [=] (auto const & it) {
      return thodd::collect(it, collector) ;
    } ;
  }

  /** 
   * @brief  Retourne le résultat d'un flow d'exécution dont le point 
   * de départ est un iterateur
   * @param  it: iterateur de départ 
   * @param  first_it_action:  
   * @param  it_actions: 
   * @retval 
   */
  auto flow (auto const & it, 
             auto const & first_it_action, 
             auto const & ...  it_actions) {
    if constexpr (sizeof...(it_actions) > 0)
      return flow(first_it_action(it), it_actions...) ;
    else 
      return first_it_action(it) ;
  }
}

#endif