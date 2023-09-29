# cse101-pt

CSE-101 Programming Assignment Repository

## How to work on an assignment

- For each assignment you will need to create a new branch and work on the new branch. In order to create a new branch, you can use the following code (make sure you use lower case, e.g: pa1, pa2, pa3, ...):
```bash
git checkout -b pa{ID}
```
- Create a folder to for the assignment and work on this directory for your assignment:
```bash
mkdir pa{ID}
```
- When you make sufficient changes in your code and want to commit your changes, you can use following code:
```bash
git add {modified-files}
git commit -m {explanatory-message-for-the-changes}
``` 
- Above code will mark your changes on your local computer. In order to update your gitlab repository you need to push your changes using below code (you may be asked your password or passphrase):
```bash
git push
```

## How to test your code

- We provide public tests for you to test your code. Test files are contained in `cse-101-public-tests` folder. Note that this folder is just a reference to an other public repository at a certain commit id which continuously gets updated. 
- In order to obtain actual files within this directory. Run the following command:
```bash
git submodule update --init
``` 

- We will announce the release of tests on regular basis. Once announced, run the following command to obtain the updated test files for specific assignment. This commead will update the local test files as well as the remote repository:

```bash
git submodule update --remote
git add cse-101-public-tests
git commit -m “add pa{ID} cse-101-public-tests”
git push
```

- Once obtained you can run the tests as follows:

```bash
cd pa{ID} # Go into specific asssignment folder in your working directory
chmod +x ./../cse-101-public-tests/pa{ID}/pa{ID}.sh
./../cse-101-public-tests/pa{ID}/pa{ID}.sh