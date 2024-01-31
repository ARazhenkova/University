import { ComponentFixture, TestBed } from '@angular/core/testing';

import { LoadTasksComponent } from './load.tasks.component';

describe('LoadTasksComponent', () => {
  let component: LoadTasksComponent;
  let fixture: ComponentFixture<LoadTasksComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ LoadTasksComponent ]
    })
    .compileComponents();

    fixture = TestBed.createComponent(LoadTasksComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
