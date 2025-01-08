## Pokec Social Network Analysis : Discrete Structure Project

- This project was developed as part of the Discrete Structures course to analyze the Pokec social network dataset using C++.
  
This repository contains a C++ project that performs various discrete mathematical analyses on the Pokec social network dataset. The project implements concepts such as propositions, quantifiers, sets, relations, functions, graph theory, and more.

### Overview
Pokec is a popular Slovak social network that connects over 1.6 million users. This project uses anonymized data from the Pokec dataset to explore discrete structures concepts in a real-world context. The primary objectives include analyzing user profiles and relationships using mathematical and programming techniques.

### Features
1. **Propositions**
   - Verify implications and biconditional statements about users.
2. **Quantifiers**
   - Find users that satisfy specific conditions.
   - Check universal properties across regions.
3. **Set Operations**
   - Perform union, intersection, and complement operations on user sets.
4. **Functions**
   - Map user attributes and verify injectivity and surjectivity.
5. **Relations**
   - Check reflexivity, symmetry, and transitivity in user friendships.
6. **Induction**
   - Prove dataset properties using mathematical induction.
7. **Permutations and Combinations**
   - Calculate groupings and arrangements based on user attributes.
8. **Counting**
   - Generate reports on public profiles, regional distributions, and more.
9. **Trees**
   - Represent user relationships as tree structures.
   - Perform preorder, postorder, and BFS traversals.
10. **Graphs**
    - Create bipartite graphs and minimum spanning trees.

### File Structure
- **src/**: Contains the source code.
- **data/**: Placeholder for the large dataset files (see below).
- **README.md**: Project documentation.
- **output/**: Directory for saving screenshots or logs of results.

### Handling Large Dataset Files
The dataset files (`soc-pokec-profiles.txt` and `soc-pokec-relationships.txt`) are too large to be uploaded to GitHub. Follow these steps to work with the dataset:
1. Download the dataset from [Pokec Social Network Dataset provided by *Jure Leskovec of Stanford University*](https://snap.stanford.edu/data/soc-Pokec.html).
2. Place the files in your corresponding directory.
3. Update the file paths in the source code if needed.

### How to Run
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/Pokec-Discrete-Structures-Analysis.git
   cd Pokec-Discrete-Structures-Analysis
   ```
2. Compile and run the project:
   ```bash
   g++ -o main src/main.cpp
   ./main
   ```
3. Follow the on-screen menu to explore different analyses.

### Dependencies
- Just dowload the data from provided Link.
**Tips:**
- As Data is too large to handle you can read the data for specified user.
- Also Download the readme file from provided link to know more about dataset. 

### Contributors
For any questions or suggestions, feel free to contact us:
- [Muhammad Hassan](https://github.com/MHassan05)   (mh873030@gmail.com)
- [Hamza Shabbir](https://github.com/Hamza-s2004)   (toAdd)

### License
This project is licensed under the MIT License. See the LICENSE file for details.
