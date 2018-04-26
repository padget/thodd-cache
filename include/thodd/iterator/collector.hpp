#ifndef __thodd_cache_iterator_collector_hpp__
#  define __thodd_cache_iterator_collector_hpp__

namespace thodd {
  
  /// Un basic_collector est un foncteur qui permet d'ajouter 
  /// un élément à un container.
  template <typename collection_t, typename append_t> 
  struct basic_collector {
    using collection_type = collection_t ;

    // Fonction permettant l'ajout d'un element 
    // dans une collection de type collection_t
    append_t append ;

    // Surcharge de l'opération fonctionnel permettant l'application
    // d'append sur une collection et un item à ajouter
    void operator () (collection_type & collection, auto && item) const {
      append(collection, std::forward<decltype(item)>(item)) ;
    }
  } ;


  namespace meta {
    /// Meta type portant une information de type.
    template <typename type_t>
    struct type {
    } ;
  }

  /** 
   * @brief  Construit un basic_collector à partir d'un type de container 
   * et d'une fonction permettant l'ajout d'élément dans ce type de container
   * @param  container_t: type du container 
   * @param  append: fonction permettant l'ajout dans container_t
   */
  template <typename collection_t, 
            typename append_t>
  constexpr basic_collector<collection_t, append_t>
  make_collector(meta::type<collection_t> const&, 
                 append_t const & append) {
    return {append} ;
  }

  /** 
   * @brief  Opération terminale permettant de collecté les éléments d'un iterator 
   * dans un nouveau container
   * @param  it: iterator dont on veut collecter les éléments 
   * @param  collector:  fonction permettant l'ajout des éléments d'it dans un 
   * nouveau container de type container_t
   */
  template <typename collector_t>
  typename collector_t::collection_type 
  collect (auto const & it, collector_t const & collector) {
    typename collector_t::collection_type collection ;
    auto cursor = it ;

    while (has_next(cursor)) {
      collector(collection, in(cursor)) ;
      next(cursor) ; 
    }

    return collection ;
  }
}

#endif 