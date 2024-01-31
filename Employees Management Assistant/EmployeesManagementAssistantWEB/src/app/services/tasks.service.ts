import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { AppAdditionalConfigurations } from '../app-additional-configurations';
import { Task } from '../models/task.model';
import { User } from '../models/user.model';

@Injectable({
  providedIn: 'root'
})
export class TasksService {

  constructor(private http: HttpClient) { }

  loadTasks(user: User): Observable<Task[]>{
      return this.http.post<Task[]>(AppAdditionalConfigurations.baseURL + "/tasks/v1", user);
  }

  searchTask(task: Task): Observable<Task> {
    return this.http.post<Task>(AppAdditionalConfigurations.baseURL + '/tasks/search/v1', task);
  }

  createTask(task: Task) {
    return this.http.put(AppAdditionalConfigurations.baseURL + '/tasks/create/v1', task);
  }

  updateTask(task: Task) {
    return this.http.put(AppAdditionalConfigurations.baseURL + '/tasks/update/v1', task);
  }

  deleteTask(taskID: number) {
    return this.http.put(AppAdditionalConfigurations.baseURL + '/tasks/delete/v1', taskID);
  }
}
