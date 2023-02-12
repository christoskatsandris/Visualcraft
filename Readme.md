# Visualcraft
### Χρήστος Κατσανδρής - 1072755

---

## Τι έχει γίνει μέχρι τώρα

- Σχεδίαση N x N x N voxel grid. Μέγιστο μέγεθος πριν πέσει το frame rate N = 100.
- Δημιουργία height map, που ακολουθεί Perlin noise. Μετακίνηση της κάθε στήλης του grid, σύμφωνα με το αντίστοιχο στοιχείο του height map.
- Εφαρμογή textures. Έχουν χρησιμοποιηθεί 6 διαφορετικά textures:
  - **Water:** χρησιμοποιείται σαν overlay για τα voxels που έχουν $y<-0.5$.
  - **Sand:** χρησιμοποιείται για τα voxels που έχουν $y<0.5$.
  - **Grass path side και grass path top:** χρησιμοποιείται για τα voxels που έχουν $y>1.5$, αλλά δεν βρίσκονται στην κορυφή της αντίστοιχης στήλης του grid.
  - **Grass block side και grass block top:** χρησιμοποιείται για τα voxels που βρίσκονται στην κορυφή της αντίστοιχης στήλης του grid.
- Δημιουργία ενός ενιαίου texture atlas.
- Optimization: σχεδίαση μόνο της κορυφής της κάθε στήλης του grid. Έτσι πλέον σχεδιάζεται ένα grid N x 1 x N. Μέγιστο μέγεθος πριν πέσει το frame rate N = 1000.
- Τοποθέτηση δέντρων και βράχων. Έχουν χρησιμοποιηθεί 3D μοντέλα, τα οποία έχουν γίνει voxelized με αλγόριθμο καταμέτρησης των vertices. Έχουν χρησιμοποιηθεί 4 επιπλέον textures: **stone, acacia log, acacia log top, acacia leaves**.
- Camera manipulation:
  - Η κάμερα δεν ίπταται, αλλά περπατάει πάνω στα blocks.
  - Όταν κάποιο block βρίσκεται σε χαμηλότερο υψόμετρο, η κάμερα πέφτει.
  - Με το space, η κάμερα πηδάει.
  - Όταν η κάμερα έχει μπροστά/πίσω/δεξιά/αριστερά κάποιο εμπόδιο, μπλοκάρεται η κίνηση προς εκείνη την κατεύθυνση.

---

## Τι άλλο πρέπει να γίνει

- Optimization: σε blocks που περιτριγυρίζονται από άλλα blocks, να μην γίνονται rendered οι αντίστοιχες έδρες.
- Το water overlay να βρίσκεται πάντα στην ίδια στάθμη. Η κάμερα να επιπλέει.
- Τοποθέτηση ζώων. Τα ζώα ίσως δεν πρέπει να είναι voxelized 3D μοντέλα, επειδή, λόγω χαμηλού resolution, θα πρέπει να βγουν πάρα πολύ μεγάλα. Η ιδέα είναι να αποτελούνται από δύο voxels και να τοποθετηθεί το κατάλληλο texture σε αυτά.
- Φωτισμός, σκίαση
- Ray casting
- Inventory
- Optimization: chunking
- Απέραντος κόσμος