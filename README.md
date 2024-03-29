# Search For A Star finalist 2024 repo, building a game upon a barebones DirectX11 graphical framework.

## Information

![s1](https://github.com/TaniCorn/sfas-2024/assets/63819551/5530efd9-c82e-4348-bd4d-9bd755cf49b3)

This project was originally written in a week for the 2024 SFAS. I managed to get into the finalist and recieved amazing feedback, which for the most part has been implemented.
You can check out the itchio here https://tanicorn.itch.io/sfas-pirate-bay

What can you expect from this page?

- [Initial project design and thoughts](#project-design)
- [Feedback recieved and addressed](#individual-feedback-recieved)
- [Retrospective](#retrospect)


What can you expect from the code?

- Smart pointers now implemented
- Clean code with self-explained variables and function names, with comments to explain certain areas.
- Concepts like polymorphism, object pooling, shaders and graphics system, level loading

What can you expect from the game?

- A quick short tower defence that quickly scales from easy to difficult
- A fun and simple design that allows quick mastery and skill
- Pirates with planes

## Project supporting document
### Project Design

When I first set out on this project, I had a couple goals when looking at the codebase I was given:
1. Improve the graphical pipeline – Add some more shaders, UI, or handling of assets
2. Introduce sound to the application
3. Develop a good level loading system
4. Have a somewhat polished, fully functional game from start to finish

I managed to do everything except the sound because I had run out of time.
The idea for the game came from my love for Vampire Survivors and tower defence games. This was the original screenshot of my idea![image](https://github.com/TaniCorn/sfas-2024/assets/63819551/960421e6-bd54-407b-966c-2529abe18099)

Initially I tried to research some of the previous SFAS Programming entries but found out that most of the games made before was using a game engine, which puts the expectations for the this a little bit differently. I felt like it would be most suited to put 50% of my focus into the engine, and the other 50% into the game.

### Design Plan

Graphics
 - I also want to improve the graphical pipeline, instead of creating a texture, a shader for that texture, and a renderable for that shader; which I understood that it would be more efficient for use cases where there was a lot of assets using the same texture, it was just a bit clunky to use. 
 - The design I had envisioned for the system was to create textures that were referenced by Renderables, and shaders could render anything with any texture.

 Levels
 - Having the Game.h be the main game application while the levels would live inside it. I thought it would be a good idea to replicate the IApplication to the ILevel as much as possible. With one difference being the IsValid function changes to a function that allows current levels to switch to a different level by returning an enum value.

 AI
 - AI would be really simple, since our base would be in the middle we don’t need to do any advanced pathfinding or creating paths for them to follow, instead we’d just make them go to the target straight on.

 Tower and Enemies
 - Initially I planned to have towers and enemies function with the prototype pattern, however as I was reaching the end of the project, the extra work to implement specialised functionality and extra art assets that would make sense with the theme was not worth the limited time I had.

### Dev Diary
The application had some existing problems that needed to be fixed.
1.	It could only load DDC textures -> Added WIC Loading into the create texture function
2.	There was no true DeltaTime -> Created my own DeltaTime class following cross-platform architecture
3.	There was a data leak – After identifying that it was simply coming from not having virtual destructors

Graphic Pipeline handling data
- I wanted to ensure that the graphics pipeline handled all graphics assets and did all the garbage collection, which is what I imagined the full engine is supposed to do. So I made a distinction between registered assets and rendered assets. 
- Assets would automatically be added to a set when being rendered, but could be removed from render but not removed from the register of assets. I planned to allow them to be manually removed but eventually found no need for it. This allowed the Graphics->Cleanup() function to truly cleanup every single asset.

1 Param shader class
- I eventually found that for the purpose of my game I only needed one extra shader class, which was just receiving 4 float params. This translated into 1 C++ class and 2 fx files

Interface trap
- I started making everything inherit from IClasses I had made, however I had a look back on what they actually were. The interface classes that I was making followed the original code; not being true interface classes. I started to develop the mindset that it was fine, however as soon as I realised I was double and triple inheriting from non-true-interface classes, I took a step back and started to re-implement them as component classes.


# Post-SFAS

I've done some cleanup and worked on the overall, and individual feedback I recieved from the judges.

I gave myself a few days, as I'm still working on my honours project and I didn't want this to take up too much of my time.

Original Search For A Star 2024 finalist code: [Original Branch](https://github.com/TaniCorn/sfas-2024/tree/original)

## Retrospect

- I really really enjoyed this project. It's nice being able to do a project without the pressure to learn entirely new concepts and getting marked on it. On this I could purely focus on my code, rather than whether the new thing works. 

- Recieving all this feedback has been great as well, it's let me see where I'm weak at and what I needed to work on

- I FINALLY worked on smart pointers, and you know what? I really like them, the concept of ownership never really occured in my head until I started using smart pointers. Plus it just makes the code architecture better. I'll be trying to use them more in the future.

## Individual Feedback Recieved
 - [ ] Do serialization so that things don't need to be stored in code. - Will not be able to do in time
 - [x] Add some comments describing my intention
 - [x] Look at the compiler warnings!
 - [x] GameLevel class leaks memory of many created objects
 - [ ] Enum for selecting levels scales poorly, and chosen name "Level" can lead to confusion, since its not the instance just an identifier. <- Took too long to think of a good solution
 - [x] Naming could be better, Enemy::Target for base health isn't great.
 - [x] Comment the pooling system
 - [x] Smaller commits of functional units would be better
 - [x] Parameter passed to DirectX11Billboard::Update shadows a memer variable in the class
 - [x] Avoid direct access of member variables.
 - [x] Mark virtual overidden methods both as virtual and overriden.
 - [x] Initialize all variables and pay attention to implicit conversions.
 - [ ] Try to incorporate Entity-Component more in order to achieve code-reusability. The code seems a bit monolithic<- Will not be able to do in time
 - [x] Some parts of the code was really dense and hard to read.
 - [x] Split longer methods, unless performance is involved.
 - [x] Const-correct principle.
 - [x] Avoid hard-coded data, prefer parametrized code instead of refactoring hard coded data.
 - [ ] Use ini/asset files to load information into the game, Levels, Enemy types. <- Will not be able to do in time
 - [x] Use smart pointers.
 - [x] Free momenory when you have allocated.

## Broader Feedback Recieved

Now we'll move onto the broader feedback for all SFAS finalists. **_I've marked some of these in bold italics because I didn't think they applied to my project_**

### INPUT
 - [x] Make sure to use the provided abstraction for input
 - [x] Use DX Input rather than windows messages

### POD
 - [x] Recommended to pass Plain Old Data types as const reference
> Non-POD's are structs and classes
> Some types can be passed by value if they'll fit in vector registers
> Conversely pass POD types as const values as long as they are 32bit, as the 32 bit copy will take less space on the stack than the address on a 64bit platform if you pass by pointer or reference.

### BEST PRACTICES
 - [x] Using square of distance for collision checks avoids expensive square root function
 - [x] Function parameters should be const when possible
 - [ ] **_For parameters where unit is unclear, degress or radians comment it_**
 - [x] Suggest using enum classes instead of enums
 - [x] Don't make member variables public without good reason, use accessors by preference
 - [ ] **_Share assets if you can, use reference counted objects or a simple asset database_**
 - [ ] Avoid hardcoding sizes of arrays, position of onscreen elements. At least use constants, preferably data files. <- Ini/asset files feedbakc. Unable to do in time
 - [x] Careful of variable scope
 - [x] Be careful of variable shadowing - two variables with the same name but in different overlapping scopes.
 - [x] Recommend using assertions or if() to avoid exceptions
 - [ ] **_Avoid using parameterised macros, prefer inline functions, const variables, or const expressions. Passion complex expressions as parameters to macros can often cause unexpected side effects_**
 - [x] Improve code reuse by turning code fragments into small functions, don't worry about performance
 - [ ] **_Don't write entire function definitions in class declarations, this isn't C#_**
 - [ ] **_Be careful using dynamic cast, it can be expensive for performance._**
 - [ ] **_Classic loop iterations from 0 to N-1 should not be <= N-1 but < N_**
 - [x] Take time to create a folder structure for source files
 - [x] Watch the size of functions, break them down.

### CODING STANDARDS
 - [x] Tidy up a commit and remove any commented out code unless it's a good reason to keep it around.
 - [x] Just be consistant in your coding standards. If you are making changes in 3rd part code, follow their standards.
 - [x] Don't have line lengths too long, they're excessive and hard to read.
 - [ ] **_Initialiser lists can be more readable when spread across multiple lines_**
 - [x] Prefer using nullptr over NULL
 - [x] K&R braces are harder to read, put braces on seperate lines
 - [ ] **_Put inline definitions either below the class declaration or if you have a lot of them, in a seperate .inl file. This makes class declaration shorter and easier to read._**
 - [x] Best to check for pointer being non-null and/or assert rather than assume the delete implementation handles it appropriately
 - [x] Recomment avoiding using auto unless the type decleration would be particularly long/complex

### SOURCE CONTROL
 - [x] Check it works on another machine
 - [x] Beware of absolute paths in project configs
 - [ ] **_If you use 3rd part libs, make sure it's clear where and how to acquire libs_**
 - [ ] Filter out intermediate files 
 - [x] Developers involved in recruitement will want to build your project to see if you've delivered it carefully enough that it build correctly
 - [x] Build both debug and release versions.
 - [x] Try to avoid disabling specific warnings, if you can't fix the issue, use a #pragma to disable it and comment it accordingly. Admit rather than hide.




![s2](https://github.com/TaniCorn/sfas-2024/assets/63819551/ca5059bc-62ff-4f54-8087-4148ab5d9205)
