#ifndef __thodd_cache_query_select_hpp__
#  define __thodd_cache_query_select_hpp__

namespace thodd::cache {

  

  /**
   * from (t, 
   *  select("name","firstname"), 
   *  where(
   *    and(
   *      equal("name", value("robert")))) ;  
   */

  /// Un selector représente un ensemble de column d'une table à extraire
  struct selector {
    /// Noms des colonnes dont on veut une extraction
    std::vector<std::string> columns ;
  } ;

  size_t indexof (auto const & item, auto const & container) {
    int index = 0 ;
    return as_stream(container)
      .foreach([&item, &index] (auto const & val) {return item == val ? acc : acc + 1 ; }, container.size())
  }

  /** 
   * @brief  Prépare la sélection dans un table à partir d'un selector
   * @param  t: table source de l'extraction 
   * @param  s: selector permettant de décrire l'extraction souhaitée
   * @retval résultat de la préparation de l'extraction
   */
  from (table const & t, selector const & s) {
    std::vector<int> indexes ;
    for (auto const & scolname : s.columns) {
      for (auto const & head : t.header) {
        if (head.
      }
    }

    return thodd::as_stream(t.data)
      .map([s] (auto const & record) {
        return thodd::as_stream(record)
          .join(s.columns)
      }) ;
  }
}

#endif