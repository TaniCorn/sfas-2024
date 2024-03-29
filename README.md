# Search For A Star finalist 2024 repo, building a game upon a barebones DirectX11 graphical framework.

## Post-SFAS
I've done some cleanup and worked on the overall, and individual feedback I recieved from the judges.
I gave myself a few days, as I'm still working on my honours project and I didn't want this to take up too much of my time.
Original Search For A Star 2024 finalist code: [Original Branch](https://github.com/TaniCorn/sfas-2024/tree/original)

### Retrospect
I really really enjoyed this project. It's nice being able to do a project without the pressure to learn entirely new concepts and getting marked on it. On this I could purely focus on my code, rather than whether the new thing works. 
Recieving all this feedbakc has been great as well, it's let me see where I'm weak at and what I needed to work on
I FINALLY worked on smart pointers, and you know what? I really like them, the concept of ownership never really occured in my head until I started using smart pointers. Plus it just makes the code architecture better. I'll be trying to use them more in the future.


### Individual Feedback Recieved
 - [] Do serialization so that things don't need to be stored in code. - Will not be able to do in time
 - [x] Add some comments describing my intention
 - [x] Look at the compiler warnings!
 - [x] GameLevel class leaks memory of many created objects
 - [] Enum for selecting levels scales poorly, and chosen name "Level" can lead to confusion, since its not the instance just an identifier. <- Took too long to think of a good solution
 - [x] Naming could be better, Enemy::Target for base health isn't great.
 - [x] Comment the pooling system
 - [x] Smaller commits of functional units would be better
 - [x] Parameter passed to DirectX11Billboard::Update shadows a memer variable in the class
 - [x] Avoid direct access of member variables.
 - [x] Mark virtual overidden methods both as virtual and overriden.
 - [x] Initialize all variables and pay attention to implicit conversions.
 - [] Try to incorporate Entity-Component more in order to achieve code-reusability. The code seems a bit monolithic<- Will not be able to do in time
 - [x] Some parts of the code was really dense and hard to read.
 - [x] Split longer methods, unless performance is involved.
 - [x] Const-correct principle.
 - [x] Avoid hard-coded data, prefer parametrized code instead of refactoring hard coded data.
 - [] Use ini/asset files to load information into the game, Levels, Enemy types. <- Will not be able to do in time
 - [x] Use smart pointers.
 - [x] Free momenory when you have allocated.

Now we'll move onto the broader feedback for all SFAS finalists. **_I've marked some of these in bold italics because I didn't think they applied to my project_**

### Broader Feedback Recieved
#### INPUT
 - [x] Make sure to use the provided abstraction for input
 - [x] Use DX Input rather than windows messages

#### POD
 - [x] Recommended to pass Plain Old Data types as const reference
  > Non-POD's are structs and classes
> 
	> Some types can be passed by value if they'll fit in vector registers
> 
	> Conversely pass POD types as const values as long as they are 32bit, as the 32 bit copy will take less space on the stack than the address on a 64bit platform if you pass by pointer or reference.

#### BEST PRACTICES
 - [x] Using square of distance for collision checks avoids expensive square root function
 - [x] Function parameters should be const when possible
 - [] **_For parameters where unit is unclear, degress or radians comment it_**
 - [x] Suggest using enum classes instead of enums
 - [x] Don't make member variables public without good reason, use accessors by preference
 - [] **_Share assets if you can, use reference counted objects or a simple asset database_**
 - [] Avoid hardcoding sizes of arrays, position of onscreen elements. At least use constants, preferably data files. <- Ini/asset files feedbakc. Unable to do in time
 - [x] Careful of variable scope
 - [x] Be careful of variable shadowing - two variables with the same name but in different overlapping scopes.
 - [x] Recommend using assertions or if() to avoid exceptions
 - [] **_Avoid using parameterised macros, prefer inline functions, const variables, or const expressions. Passion complex expressions as parameters to macros can often cause unexpected side effects_**
 - [x] Improve code reuse by turning code fragments into small functions, don't worry about performance
 - [] **_Don't write entire function definitions in class declarations, this isn't C#_**
 - [] **_Be careful using dynamic cast, it can be expensive for performance._**
 - [] **_Classic loop iterations from 0 to N-1 should not be <= N-1 but < N_**
 - [x] Take time to create a folder structure for source files
 - [x] Watch the size of functions, break them down.

CODING STANDARDS
 - [x] Tidy up a commit and remove any commented out code unless it's a good reason to keep it around.
 - [x] Just be consistant in your coding standards. If you are making changes in 3rd part code, follow their standards.
 - [x] Don't have line lengths too long, they're excessive and hard to read.
 - [] **_Initialiser lists can be more readable when spread across multiple lines_**
 - [x] Prefer using nullptr over NULL
 - [x] K&R braces are harder to read, put braces on seperate lines
 - [] **_Put inline definitions either below the class declaration or if you have a lot of them, in a seperate .inl file. This makes class declaration shorter and easier to read._**
 - [x] Best to check for pointer being non-null and/or assert rather than assume the delete implementation handles it appropriately
 - [x] Recomment avoiding using auto unless the type decleration would be particularly long/complex

SOURCE CONTROL
 - [x] Check it works on another machine
 - [x] Beware of absolute paths in project configs
 - [] **_If you use 3rd part libs, make sure it's clear where and how to acquire libs_**
 - [] Filter out intermediate files 
 - [x] Developers involved in recruitement will want to build your project to see if you've delivered it carefully enough that it build correctly
 - [x] Build both debug and release versions.
 - [x] Try to avoid disabling specific warnings, if you can't fix the issue, use a #pragma to disable it and comment it accordingly. Admit rather than hide.



## SFAS Original
This project was created within a week for the Search For A Star 2024 compeition. 
Inside you'll find a fully complete game built from an existing graphical engine using DirectX.
You can check out the itchio here https://tanicorn.itch.io/sfas-pirate-bay

I may come back to this project in the future to experiment with adding in smart pointers to really tidy it up.
![s1](https://github.com/TaniCorn/sfas-2024/assets/63819551/5530efd9-c82e-4348-bd4d-9bd755cf49b3)
![s2](https://github.com/TaniCorn/sfas-2024/assets/63819551/ca5059bc-62ff-4f54-8087-4148ab5d9205)
