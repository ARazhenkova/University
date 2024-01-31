import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { Task } from 'src/app/models/task.model';
import { AuthenticationService } from 'src/app/services/authentication.service';
import { TasksService } from 'src/app/services/tasks.service';

@Component({
  selector: 'app-create.task',
  templateUrl: './create.task.component.html',
  styleUrls: ['./create.task.component.css']
})
export class CreateTaskComponent implements OnInit {
  task: Task = new Task();

  constructor(private taskService: TasksService
            , private authenticationService: AuthenticationService
            , private router: Router) {}

  ngOnInit(): void {

  }

  createTask(): void {
    if(!this.isDataValid())
      return;

    this.task.userID = this.authenticationService.getUserID();

    this.taskService.createTask(this.task)
    .subscribe({
      next: data => {
        this.router.navigate(['tasks']);
      }
    });
  }

  onCancel(): void {
    this.router.navigate(['tasks']);
  }

  isDataValid(): boolean {
    if (this.task.name == "")
      return false;

    return true;
  }
}
