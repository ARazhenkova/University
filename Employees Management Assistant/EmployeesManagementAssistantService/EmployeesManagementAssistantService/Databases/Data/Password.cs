using System.Security.Cryptography;
using System.Text;

namespace EmployeesManagementAssistantService.Databases.Data
{
    /// <summary> Клас за работа с парола </summary>
    public class Password
    {
        #region Members

        /// <summary> Размер на хеша </summary>
        private static int _hashSize = 128;

        /// <summary> Брой итерации на хеширането </summary>
        private static int _interations = 10000;

        /// <summary> Размер на ключа за хеширане </summary>
        private static int _saltSize = 16;

        #endregion

        #region Constructor

        /// <summary> Kонструктор </summary>
        public Password(string password) 
        {
            PlanePassword = password;
            HashedPassword = "";
            Salt = "";

            Hash();
        }

        /// <summary> Kонструктор </summary>
        public Password(string password, string salt)
        {
            PlanePassword = password;
            HashedPassword = "";
            Salt = "";

            Hash(salt);
        }

        #endregion

        #region Properties

        /// <summary> Парола в чист вид </summary>
        public string PlanePassword { get; set; }

        /// <summary> Хеш </summary>
        public string HashedPassword { get; set; }

        /// <summary> Ключ </summary>
        public string Salt{ get; set; }

        #endregion

        #region Methods

        /// <summary> Хеширане на парола с PBKDF2, алгоритъм SHA512 </summary>
        public void Hash() 
        {
            try
            {
                // Генериране на ключ за хеширане
                byte[] salt = new byte[_saltSize];

                RNGCryptoServiceProvider random = new RNGCryptoServiceProvider();
                random.GetNonZeroBytes(salt);

                // Хеширане
                byte[] hashedPassword = Rfc2898DeriveBytes.Pbkdf2(Encoding.UTF8.GetBytes(PlanePassword)
                                                                , salt
                                                                , _interations
                                                                , HashAlgorithmName.SHA512
                                                                , _hashSize);

                Salt = Convert.ToBase64String(salt);
                HashedPassword = Convert.ToBase64String(hashedPassword);
            }
            catch(Exception ex)
            {

            }
        }

        /// <summary> Хеширане на парола с PBKDF2, алгоритъм SHA512 </summary>
        public string Hash(string salt)
        {
            try
            {
                // Хеширане
                byte[] hashedPassword = Rfc2898DeriveBytes.Pbkdf2(Encoding.UTF8.GetBytes(PlanePassword)
                                                                , Convert.FromBase64String(salt)
                                                                , _interations
                                                                , HashAlgorithmName.SHA512
                                                                , _hashSize);

                HashedPassword = Convert.ToBase64String(hashedPassword);
            }
            catch (Exception ex)
            {

            }

            return HashedPassword;
        }

        #endregion
    }
}
