#ifndef __thodd_cache_table_hpp__
#  define __thodd_cache_table_hpp__

#  include <list>
#  include <vector>
#  include <map>
#  include <string>
#  include <functional>
#  include <tuple>

namespace thodd::cache {

  /// Types possibles d'une colonne de table
  enum class column_type {primary_key, simple, foreign_key} ;

  /// Validité d'une contrainte
  using constraint_validity = bool ;

  /// Signature d'une fonction de contrainte pour une colonne de table
  ///     data: std::string         = donnée en entrée pour vérification
  ///     res : constraint_validity = résultat du check (valid ou invalid) 
  using constraint_f = std::function<constraint_validity(std::string const &)> ; 

  /// Description d'une colonne d'une table
  ///    constraint = contrainte de validation de la colonne
  ///    name = nom de la colonne
  ///    type = type de la colonne (pk, fk, simple)
  using column = std::tuple<column_type, constraint_f, std::string> ;

  /// index de localisation d'une méta donnée dans une colonne (tuple)
  constexpr auto ctype_idx      = 0u ;
  constexpr auto constraint_idx = 1u ;
  constexpr auto name_idx       = 2u ;

  /** 
   * @brief Obtient le type de la colonne
   * @param  col: colonne dont on veut le type
   * @retval type de la colonne
   */
  auto get_type(auto const & col) -> decltype(auto) {
    return std::get<ctype_idx>(col) ;
  }
  
  /** 
   * @brief Obtient le nom de la colonne
   * @param  col: colonne dont on veut le nom
   * @retval nom de la colonne
   */
  auto get_name(auto const & col) -> decltype(auto) {
    return std::get<name_idx>(col) ;
  }

  /** 
   * @brief  Obtient la fonction de validation des données de la colonne
   * @param  col: colonne dont on veut la fonction de validation
   * @retval fonction de validation de la colonne
   */
  auto get_constraint(auto const & col) -> decltype(auto) {
    return std::get<constraint_idx>(col) ;
  }

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