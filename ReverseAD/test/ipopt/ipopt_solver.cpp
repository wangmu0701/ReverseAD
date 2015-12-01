#include "IpIpoptApplication.hpp"
#include "IpSolveStatistics.hpp"
#include "nlp_problem.hpp"

using namespace Ipopt;

int run_app(SmartPtr<IpoptApplication> app,
            SmartPtr<TNLP> my_nlp) {
  ApplicationReturnStatus status;
  status = app->Initialize();
  if (status != Solve_Succeeded) {
    printf("\n\n*** Error during initialization!\n");
    return (int) status;
  }

  status = app->OptimizeTNLP(my_nlp);

  if (status == Solve_Succeeded) {
    // Retrieve some statistics about the solve
    Index iter_count = app->Statistics()->IterationCount();
    printf("\n\n*** The problem solved in %d iterations!\n", iter_count);

    Number final_obj = app->Statistics()->FinalObjective();
    printf("\n\n*** The final value of the objective function is %e.\n", final_obj);
  }

  return (int) status;
}
int main(int argv, char* argc[])
{
  // Create an instance of your nlp...
  SmartPtr<TNLP> my_nlp = new NlpProblem();

  // Create an instance of the IpoptApplication
  SmartPtr<IpoptApplication> app = new IpoptApplication();

  // Initialize the IpoptApplication and process the options
  app->Options()->SetNumericValue("tol", 1e-12);
  app->Options()->SetStringValue("hessian_approximation", "limited-memory");
  run_app(app, my_nlp);
  
  my_nlp = new NlpProblem();
  app = new IpoptApplication();
  app->Options()->SetNumericValue("tol", 1e-12);
  //app->Options()->SetStringValue("hessian_approximation", "limited-memory");
  run_app(app, my_nlp);

/*
  ApplicationReturnStatus status;
  status = app->Initialize();
  if (status != Solve_Succeeded) {
    printf("\n\n*** Error during initialization!\n");
    return (int) status;
  }

  status = app->OptimizeTNLP(my_nlp);

  if (status == Solve_Succeeded) {
    // Retrieve some statistics about the solve
    Index iter_count = app->Statistics()->IterationCount();
    printf("\n\n*** The problem solved in %d iterations!\n", iter_count);

    Number final_obj = app->Statistics()->FinalObjective();
    printf("\n\n*** The final value of the objective function is %e.\n", final_obj);
  }

  return (int) status;
*/
  return 0;
}
