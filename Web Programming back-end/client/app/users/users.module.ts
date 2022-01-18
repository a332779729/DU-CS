import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { FormsModule } from '@angular/forms';


import { RouterModule, Routes } from '@angular/router';

import { TooltipModule } from 'ngx-bootstrap';

import { BrowserAnimationsModule } from '@angular/platform-browser/animations';

import { UsersComponent } from './users.component';

export const ROUTES: Routes = [
  { path: 'users/:id', component: UsersComponent },
];

@NgModule({
  imports: [
    BrowserModule,
    FormsModule,
    BrowserAnimationsModule,
    RouterModule.forChild(ROUTES),

    TooltipModule.forRoot(),
  ],
  declarations: [
    UsersComponent
  ],

  exports: [
    UsersComponent
  ],

  providers: [
  ]
})
export class UsersModule {}
