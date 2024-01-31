import { Component, OnInit } from '@angular/core';
import { ActivatedRoute, Router } from '@angular/router';
import { Task } from 'src/app/models/task.model';
import { AuthenticationService } from 'src/app/services/authentication.service';
import { TasksService } from 'src/app/services/tasks.service';

@Component({
  selector: 'app-update.task',
  templateUrl: './update.task.component.html',
  styleUrls: ['./update.task.component.css']
})
export class UpdateTaskComponent implements OnInit {
  task: Task = new Task();

  constructor(private activatedRouter: ActivatedRoute
            , private taskService: TasksService
            , private authenticationService: AuthenticationService
            , private router: Router) {

  }

  ngOnInit(): void {
      this.activatedRouter.paramMap.subscribe({
          next: (params) => {
            const id = Number(params.get('id'));
            const externalPresentation = params.get('externalPresentation');

            if (id == null)
              return;

            if (externalPresentation == null)
              return;

            this.task.id = id;
            this.task.externalPresentation = externalPresentation;

            this.taskService.searchTask(this.task)
            .subscribe({
              next: (response) => {
                this.task = response;
              },
              error: (response) => {
                this.router.navigate(['tasks'])
              }
            })
          }
      })
  }

  updateTask(): void {
    if(!this.isDataValid())
      return;

    this.task.userID = this.authenticationService.getUserID();

    this.taskService.updateTask(this.task)
    .subscribe({
      next: (response) => {
        this.router.navigate(['tasks'])
      }
    });
  }

  onCancel(): void {
    this.router.navigate(['tasks'])
  }

  isDataValid(): boolean {
    if (this.task.name == "")
      return false;
      
    return true;
  }
}
