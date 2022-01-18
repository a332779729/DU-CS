import {Component, OnInit} from '@angular/core';
import {HttpClient} from '@angular/common/http';
import {RecipeService} from '../../components/services/recipe.service';
import {Recipe} from '../../components/interfaces/Recipe';
import {CreateRecipeComponent} from '../../components/modals/create-recipe.component';
import {UpdateRecipeComponent} from '../../components/modals/update-recipe.component';
import {BsModalService} from 'ngx-bootstrap';

@Component({
  selector: 'recipe',
  template: require('./recipe.html'),
  styles: [require('./recipe.scss')],
})
export class RecipeComponent implements OnInit {

  private recipes: Recipe[];
  static parameters = [HttpClient, RecipeService, BsModalService];

  constructor(private http: HttpClient, private recipeService: RecipeService, private modalService: BsModalService) {
    this.http = http;
    this.recipeService = recipeService;
    this.modalService = modalService;
    this.getRecipeData();
  }

  public getRecipeData() {
    this.recipeService.getAllRecipes()
      .then(response => {
        this.recipes = response.recipes as Recipe[];
      })
      .catch(this.handleError);
  }

  private handleError(error: any): Promise<any> {
    console.error('Something has gone wrong', error);
    return Promise.reject(error.message || error);
  }

  public updateRecipe(recipe: Recipe) {
    const initialState = {
      recipe
    }
    const modalRef = this.modalService.show(UpdateRecipeComponent, {initialState});
    modalRef.content.recipeToUpdate.subscribe(() => {
      this.recipeService.updateRecipe(recipe)
        .then(updatedRecipe => {
          console.log("updatedRecipe", updatedRecipe);
          modalRef.content.formInfo = `Recipe updated!`;
        })
        .catch(err => {
          console.log(err);
          modalRef.content.formError = "error";
        });
    });
  }

  public createRecipe() {
    const modalRef = this.modalService.show(CreateRecipeComponent);
    modalRef.content.recipeToCreate.subscribe(recipeToCreate => {
      this.recipeService.createRecipe(recipeToCreate)
        .then(createdRecipe => {
          modalRef.content.formInfo = `Recipe ${createdRecipe._id} created!`;
        })
        .catch(err => {
          console.log(err);
          modalRef.content.formError = err.error.message;
        });
    });
  }

  public delete(recipe) {
    this.recipeService.remove(recipe).then(deletedRecipe => {
        this.recipes.splice(this.recipes.indexOf(deletedRecipe), 1);
    });
  }

  ngOnInit() {
  }
}
