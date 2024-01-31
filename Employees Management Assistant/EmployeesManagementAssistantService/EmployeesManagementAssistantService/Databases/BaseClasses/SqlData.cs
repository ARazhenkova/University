
namespace EmployeesManagementAssistantService.Databases.BaseClasses
{
    /// <summary> Типове данни в SQL </summary>
    public enum SqlDataTypes
    {
        INT = 0,
        FLOAT,
        STRING,
        DATETIME,
        BOOLEAN,
    }

    /// <summary> Име и стойтност на поле от базата данни </summary>
    public class SqlData
    {
        #region Constructors

        /// <summary> Kонструктор </summary>
        /// <param name = "index"> Индекс на колоната </param>
        /// <param name = "name"> Име на колоната </param>
        /// <param name = "sqlDataType"> Тип на колоната </param>
        public SqlData(long index, string name, SqlDataTypes sqlDataType)
        {
            Index = index;
            Name = name;
            SqlDataType = sqlDataType;
        }

        #endregion

        #region Properties

        /// <summary> Пореден номер в SQL таблицата </summary>
        public long Index { get; private set; }

        /// <summary> Име на колоната </summary>
        public string Name { get; private set; }

        /// <summary> Стойност на колоната </summary>
        public string Value { get; set; }

        /// <summary> Тип на данната </summary>
        public SqlDataTypes SqlDataType { get; private set; }

        #endregion
    }
}
