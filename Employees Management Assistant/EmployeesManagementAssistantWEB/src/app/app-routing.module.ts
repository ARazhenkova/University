import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { LoadTasksComponent } from './components/tasks/load.tasks/load.tasks.component';
import { CreateTaskComponent } from './components/tasks/create.task/create.task.component';
import { UpdateTaskComponent } from './components/tasks/update.task/update.task.component';
import { LoginComponent } from './components/login/login.component';
import { IsLoggedInGuard } from './guards/is-logged-in.guard';
import { IsLoggedOutGuard } from './guards/is-logged-out.guard';
import { ChangePasswordComponent } from './components/change-password/change-password.component';

const routes: Routes = [
  { 
    path: '',
    component: LoginComponent,
    canActivate: [IsLoggedOutGuard],
  },
  { 
    path: 'tasks',
    component: LoadTasksComponent,
    canActivate: [IsLoggedInGuard],
  },
  { 
    path: 'tasks/create',
    component: CreateTaskComponent,
    canActivate: [IsLoggedInGuard]
  },
  { 
    path: 'tasks/update/:id/:externalPresentation',
    component: UpdateTaskComponent,
    canActivate: [IsLoggedInGuard],
  },
  { 
    path: 'change-password',
    component: ChangePasswordComponent,
    canActivate: [IsLoggedInGuard],
  }
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
