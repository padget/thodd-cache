#ifndef __thodd_cache_table_hpp__
#  define __thodd_cache_table_hpp__

#  include <list>
#  include <vector>
#  include <map>
#  include <string>

namespace thodd::cache {
  /// Types possibles d'une colonne de table
  enum class column_type {primary_key, simple, foreign_key} ;

  /// Description d'une colonne d'une table
  ///    type = type de la colonne (pk, fk, simple)
  ///    name = nom de la colonne
  using column = std::tuple<column_type, std::string> ;
  /// Un record est une ligne de la table matchant obligatoirement 
  /// avec le header de cette derniere
  using record = std::vector<std::string> ;
  
  /** 
   * @brief Une table représente une collection de données 
   * suivant la même structure
   */
  struct table {
    /// Nom de la table
    std::string name ;
    /// Structure de la table
    std::vector<column> header ;
    /// Données présentes dans la table
    std::list<record> data ;
    /// Map automatique des indexation automatique des 
    /// données sur leur primary key
    std::map<std::string, record*> pk_index ; 
  } ;
}

#endif 