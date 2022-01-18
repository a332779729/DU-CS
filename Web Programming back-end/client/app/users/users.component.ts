import {Component, OnInit} from '@angular/core';
import * as sharedConfig from '../app.constants';
import {User} from '../../components/interfaces/User';

import {HttpClient} from '@angular/common/http';
import {UserService } from '../../components/services/user.service';
import {ActivatedRoute} from '@angular/router';
import {Observable} from 'rxjs';
import {map} from 'rxjs/operators';

import {UpdateUserComponent} from '../../components/modals/update-user.component';
import {BsModalService} from 'ngx-bootstrap';
import {CreateUserComponent} from '../../components/modals/create-user.component';

@Component({
  selector: 'users',
  template: require('./users.html'),
  styles: [require('./users.scss')],
})

export class UsersComponent implements OnInit {

  private user: User;
  public users: User[] = [];
  static parameters = [ActivatedRoute, UserService, BsModalService];

  constructor(private route: ActivatedRoute, private userService: UserService, private modalService: BsModalService) {
    this.route = route;
    this.userService = userService;
    this.getUserData();
  }

  public getUserData() {
    this.userService.getAllUsers()
      .then(response => {
        this.users = response.users as User[];
      })
      .catch(this.handleError);
  }

  public updateUser(user: User) {
    const initialState = {
      user
    }
    const modalRef = this.modalService.show(UpdateUserComponent, {initialState});
    modalRef.content.updatedUser.subscribe(() => {
      this.userService.updateUser(user)
        .then(updatedUser => {
          modalRef.content.formInfo = `User ${updatedUser._id} updated!`;
        })
        .catch(err => {
          console.log(err);
          modalRef.content.formError = err.error.message;
        });
    });
  }

  public createUser() {
    const modalRef = this.modalService.show(CreateUserComponent);
    modalRef.content.userToCreate.subscribe(userToCreate => {
      this.userService.createUser(userToCreate)
        .then(createdUser => {
          modalRef.content.formInfo = `User ${createdUser._id} created!`;
        })
        .catch(err => {
          console.log(err);
          modalRef.content.formError = err.error.message;
        });
    });
  }

  private handleError(error: any): Promise<any> {
    console.error('Something has gone wrong', error);
    return Promise.reject(error.message || error);
  }

  ngOnInit() {
    console.log("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!", this.route)
    //console.log("this.httpOptions->",this.httpOptions, "this.http",this.httpClient)
    this.route.params.subscribe(params => {
    console.log("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!", params)
      this.userService.getUserById(params.id)
        .then(user => {
          console.log("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!", user)
          this.user = user;
        });
    });
  }
}
