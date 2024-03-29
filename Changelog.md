# Visualcraft
### Χρήστος Κατσανδρής - 1072755

---

## v0.2.0 (Part B)

## Τι έχει γίνει μέχρι τώρα

- Σχεδίαση N x 1 x N voxel grid. Μέγιστο μέγεθος πριν πέσει το frame rate N = 1000.
- Δημιουργία height map, που ακολουθεί Perlin noise. Μετακίνηση της κάθε στήλης του grid, σύμφωνα με το αντίστοιχο στοιχείο του height map.
- Εφαρμογή textures και δημιουργία ενός ενιαίου texture atlas.
- Τοποθέτηση δέντρων και βράχων. Έχουν χρησιμοποιηθεί 3D μοντέλα, τα οποία έχουν γίνει voxelized με αλγόριθμο καταμέτρησης των vertices.
- Interactive camera manipulation.
- Φωτισμός με μοντέλο Phong και σκίαση. Προσομοίωση ήλιου με κυκλική περιστροφή της πηγής φωτός γύρω από τη γη.
- Ray casting για καταστροφή των πλησιέστερων μπλοκ.
- Inventory για δημιουργία μπλοκ.

---

## Τι άλλο πρέπει να γίνει

- Δημιουργία ενιαίου voxel mesh, που θα περιλαμβάνει μόνο τις ορατές έδρες των voxels της επιφάνειας.
- Τοποθέτηση ζώων και άλλων αντικειμένων. Αύξηση του resolution και σμίκρυνση του αντικειμένου.
- Δημιουργία chunks και σταδιακή σχεδίαση καθενός, για optimization. Δημιουργία απέραντου κόσμου.

---

## Σφάλματα

- Η απουσία voxel mesh δημιουργεί προβλήματα στην καταστροφή μπλοκ. Όταν το ύψος δύο γειτονικών μπλοκ διαφέρει περισσότερο από μία μονάδα, εμφανίζεται κενό κάτω από την επιφάνεια.
- Η ασυμφωνία της γεωμετρίας της γης (επίπεδη) και της γεωμετρίας του ήλιου (κυκλική) δημιουργεί προβλήματα στον φωτισμό. Κάποιες πλαϊνές έδρες των αντικειμένων εξακολουθούν να φωτίζονται, όταν ο ήλιος είναι κάτω από την επιφάνεια της γης. Επίσης, όταν ο ήλιος βρίσκεται κοντά στο ύψος της γης, υπάρχει quantization στη σκίαση.
- Για τα voxels που βρίσκονται κάτω από τη στάθμη της θάλασσας, δεν γίνεται σωστά το water overlay, ούτε επιπλέει η κάμερα στη στάθμη.
- Ορισμένες φορές, ανάλογα με τον προσανατολισμό της κάμερας σε σχέση με τις έδρες των voxels, η κάμερα δεν μπλοκάρει στα εμπόδια και διέρχεται μέσω αυτών.
