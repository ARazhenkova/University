using Microsoft.AspNetCore.Mvc;
using EmployeesManagementAssistantService.BusinessLogic;
using EmployeesManagementAssistantService.Models;
using EmployeesManagementAssistantService.Databases.Tables;
using Microsoft.AspNetCore.Authorization;

namespace EmployeesManagementAssistantService.Controllers
{
    [ApiController]
    [Route("external-tasks")]
    public class TasksController : Controller
    {
        [Authorize]
        [HttpPost]
        [Route("tasks/v1")]
        public IActionResult LoadTasks([FromBody] UserModel requestModel)
        {
            List<TaskModel> responseModels = TasksProccessor.LoadRecordsByExternalUserID(requestModel.ID);

            return Ok(responseModels);
        }

        [Authorize]
        [HttpPost]
        [Route("tasks/search/v1")]
        public IActionResult LoadTask([FromBody] TaskModel requestModel)
        {
            TasksTable tasksTable = new TasksTable();
            Databases.Data.Task task = tasksTable.LoadRecordByID(requestModel.ID);

            if (task == null)
                return NotFound();

            if (task.ExternalPresentation != requestModel.ExternalPresentation)
                return Problem();

            TaskModel responseModel = TasksProccessor.GetModelFromData(task);

            return Ok(responseModel);
        }

        [Authorize]
        [HttpPut]
        [Route("tasks/create/v1")]
        public IActionResult CreateTask([FromBody] TaskModel requestModel)
        {
            Databases.Data.Task task = TasksProccessor.GetDataFromModel(requestModel);

            TasksTable tasksTable = new TasksTable();
            tasksTable.InsertRecord(task);

            return Ok();
        }

        [Authorize]
        [HttpPut]
        [Route("tasks/update/v1")]
        public IActionResult UpdateTask([FromBody] TaskModel requestModel)
        {
            Databases.Data.Task task = TasksProccessor.GetDataFromModel(requestModel);

            if (task.ExternalPresentation != task.ExternalPresentation)
                return Problem();

            TasksTable tasksTable = new TasksTable();
            tasksTable.UpdateRecordByID(task);

            return Ok();
        }

        [Authorize]
        [HttpPut]
        [Route("tasks/delete/v1")]
        public IActionResult DeleteTask([FromBody] long requestModel)
        {
            TasksTable tasksTable = new TasksTable();
            tasksTable.DeleteRecordByID(requestModel);

            return Ok();
        }
    }
}
