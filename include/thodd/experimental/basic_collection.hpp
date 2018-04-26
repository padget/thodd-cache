#ifndef __thodd_experimental_basic_collection_hpp__
#  define __thodd_experimental_basic_collection_hpp__

#include <memory>

namespace std {
  /// Alias de type symbolisant un shared_ptr
  template <typename type_t>
  using ptr = std::shared_ptr<type_t> ;

  /** 
   * @brief  Fonction alias permettant de construire un shared_ptr
   * @param  args: argument de la construction d'une instance de type_t
   * @retval un shared_ptr sur une instance de type_t
   */
  template <typename type_t>
  inline auto make_ptr(auto && ... args) {
    return std::make_shared<type_t>(static_cast<decltype(args)&&>(args)...) ;
  }
}



namespace thodd::collection {

  template <typename type_t>
  struct basic_collection_node ;

  template <typename type_t>
  struct basic_collection_pusher {
    template<typename collection_t> 
    auto operator () (collection_t const & bc, type_t const & item) const -> collection_t const {
      auto n     = std::make_ptr<basic_collection_node<type_t>>(basic_collection_node<type_t>{item, nullptr}) ;
      auto last  = bc.last ;
    
      if (!bc.first) {
        return {n, n, bc.size + 1} ;
      } else {
        last->next = n ;
        return {bc.first, n, bc.size + 1} ;
      }
    }
  } ;
}

namespace thodd::collection {
  ///
  template <typename type_t>
  struct basic_collection_node {
    type_t data ;
    std::ptr<basic_collection_node<type_t>> next ;
  } ;

  template <typename type_t, typename constraint_t, typename pusher_t = basic_collection_pusher<type_t>>
  struct basic_collection {
    std::ptr<basic_collection_node<type_t>> first ;
    std::ptr<basic_collection_node<type_t>> last ;
    size_t size{0u} ; 
  } ;
 
   /** 
   * @brief  Retourne la taille de la liste l
   * @param  l: liste dont on veut connaitre le nombre d'élément
   */
  auto size(basic_collection<auto, auto, auto> const & bc) -> size_t {
    return bc.size ;
  }

  /** 
   * @brief  Concatène une liste avec un nouvel élément et retourne la liste résultante
   * @param  l: liste d'origine
   * @param  item: item que l'on veut accoller à la liste originelle
   * @retval Retourne la nouvelle liste contenant le nouvel élément en plus de la liste originelle
   */
  template <typename type_t, typename constraint_t, typename pusher_t>
  auto push (basic_collection<type_t , constraint_t, pusher_t> const & bc, type_t const & item) -> basic_collection<type_t, constraint_t> const {
    return constraint_t{}(item) ? pusher_t{}(bc, item) : bc ;
  }
}


namespace thodd::collection { 

  /// Représente le type d'iterateur utilisé pour une basic_collection
  template <typename type_t>
  using basic_collection_iterator = std::ptr<basic_collection_node<type_t>> ;

  /** 
   * @brief  Retourne la valeur portée par le basic_collection_iterator
   * @param  lit: basic_collection_iterator dont on veut remonter la valeur
   */
  template <typename type_t>
  auto in (basic_collection_iterator<type_t> const & bcit) -> type_t const & {
    return bcit->data ;
  }

  /** 
   * @brief  Détermine si le basic_collection_iterator n'est 
   *         pas la borne de fin de la liste
   */
  template <typename type_t>
  auto has_next (basic_collection_iterator<type_t> const & bcit) -> bool {
    return bcit != nullptr ;
  }

  /** 
   * @brief  Retourne la prochaine étape du basic_collection_iterator
   * @param  lit: iterator dont veut avancer le curseur
   */
  template <typename type_t>
  auto next (basic_collection_iterator<type_t> & bcit) -> decltype(bcit) {
    bcit = bcit->next ;
    return bcit ;
  }
}



#endif