using EmployeesManagementAssistantService.Databases.Tables;
using EmployeesManagementAssistantService.Databases.Data;
using EmployeesManagementAssistantService.Models;
using System.Text;

namespace EmployeesManagementAssistantService.BusinessLogic
{
    /// <summary> Помощен клас за обработка на заявки за задача </summary>
    public class TasksProccessor
    {
        #region Constructor

        /// <summary> Kонструктор </summary>
        public TasksProccessor()
        {

        }

        #endregion

        #region Methods

        /// <summary> Връща всияки задачи за потребител </summary>
        public static List<TaskModel> LoadRecordsByExternalUserID(long externalUserID)
        {
            // Зареждане на данни за задачата
            TasksTable tasksTable = new TasksTable();
            List<Databases.Data.Task> tasks = tasksTable.LoadRecordsByExternalUserID(externalUserID);

            // Зареждане на данни за приоритети
            TaskPrioritiesTable taskPrioritiesTable = new TaskPrioritiesTable();
            List<TaskPriority> taskPriorities = taskPrioritiesTable.LoadRecords();

            // Зареждане на данни за състояния
            TaskStatesTable taskStatesTable = new TaskStatesTable();
            List<TaskState> taskStates = taskStatesTable.LoadRecords();

            List<TaskModel> taskModels = new List<TaskModel>();
            foreach (Databases.Data.Task task in tasks)
            {
                TaskModel taskModel = GetModelFromData(task);
                taskModels.Add(taskModel);
            }

            return taskModels;
        }

        /// <summary> Попълване на данните от модел в обект </summary>
        public static Databases.Data.Task GetDataFromModel(TaskModel taskModel)
        {
            Databases.Data.Task task = new Databases.Data.Task();

            task.ID                     = taskModel.ID;
            task.DataVersion            = taskModel.DataVersion;
            task.Name                   = taskModel.Name;
            task.PriorityID             = FindTaskPriority(taskModel.Priority);
            task.StateID                = FindTaskState(taskModel.State);
            task.AssignFromID           = taskModel.UserID;
            task.Description            = taskModel.Description;
            task.ExternalPresentation   = taskModel.ExternalPresentation;

            // Ако няма външно преставяне, създаваме такова
            if (String.IsNullOrEmpty(taskModel.ExternalPresentation)) 
                task.CreateExternalPresentation();

            return task;
        }

        /// <summary> Попълване на данните от обект в модел </summary>
        public static TaskModel GetModelFromData(Databases.Data.Task task, List<TaskPriority> taskPriorities = null, List<TaskState> taskStates = null)
        {
            TaskModel taskModel = new TaskModel();

            taskModel.ID                    = task.ID;
            taskModel.DataVersion           = task.DataVersion;
            taskModel.Name                  = task.Name;
            taskModel.Description           = task.Description;
            taskModel.ExternalPresentation  = task.ExternalPresentation;

            // Попълване на името на приоритета
            if (taskPriorities == null)
            {
                // Зареждане на данни за приоритети
                TaskPrioritiesTable taskPrioritiesTable = new TaskPrioritiesTable();
                taskPriorities = taskPrioritiesTable.LoadRecords();
            }

            TaskPriority taskPriority = taskPriorities.Find(taskPriority => taskPriority.ID == task.PriorityID);
            if (taskPriority == null)
                taskModel.Priority = "Необработен";
            else
                taskModel.Priority = taskPriority.Name;

            // Попълване на името на състоянието
            if (taskStates == null)
            {
                // Зареждане на данни за състояния
                TaskStatesTable taskStatesTable = new TaskStatesTable();
                taskStates = taskStatesTable.LoadRecords();
            }

            TaskState taskState = taskStates.Find(taskState => taskState.ID == task.StateID);
            if (taskState == null)
                taskModel.State = "Необработен";
            else
                taskModel.State = taskState.Name;

            return taskModel;
        }

        /// <summary> Връща идентификатор на приоритета по името му </summary>
        public static long FindTaskPriority(string name)
        {
            long priorityID = 0;

            TaskPrioritiesTable taskPrioritiesTable = new TaskPrioritiesTable();
            List<TaskPriority> taskPriorities = taskPrioritiesTable.LoadRecords();

            TaskPriority taskPriority = taskPriorities.Find(taskPriority => taskPriority.Name == name);
            if (taskPriority != null)
                priorityID = taskPriority.ID;

            return priorityID;
        }

        /// <summary> Връща идентификатор на състояние по името му </summary>
        public static long FindTaskState(string name)
        {
            long stateID = 0;

            TaskStatesTable taskStatesTable = new TaskStatesTable();
            List<TaskState> taskStates = taskStatesTable.LoadRecords();

            TaskState taskState = taskStates.Find(taskPriority => taskPriority.Name == name);
            if (taskState != null)
                stateID = taskState.ID;

            return stateID;
        }

        #endregion
    }
}
