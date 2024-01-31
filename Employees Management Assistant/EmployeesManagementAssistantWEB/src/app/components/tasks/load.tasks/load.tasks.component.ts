import { Component, OnInit } from '@angular/core';
import { Task } from 'src/app/models/task.model';
import { User } from 'src/app/models/user.model';
import { AuthenticationService } from 'src/app/services/authentication.service';
import { TasksService } from 'src/app/services/tasks.service';

@Component({
  selector: 'app-load.tasks',
  templateUrl: './load.tasks.component.html',
  styleUrls: ['./load.tasks.component.css']
})
export class LoadTasksComponent implements OnInit {
  tasks: Task[] = [];

  constructor(private taskService: TasksService
            , private authenticationService: AuthenticationService) {

  }

  ngOnInit(): void {
    const user = new User();
    user.id = this.authenticationService.getUserID();

    this.taskService.loadTasks(user)
    .subscribe({
      next: (response) => {
        this.tasks = response;
      }
    });
  }

  onDelete(taskID: number): void {
    this.taskService.deleteTask(taskID)
    .subscribe({
      next: (response) => {
        location.reload();
      }
    });
  }

  hasTasks(): boolean {
    if (this.tasks && this.tasks.length > 0)
      return true;

    return false;
  }
}
