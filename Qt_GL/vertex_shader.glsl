#version 330

// Attributs de sommet
in vec3 sommet;
in vec3 couleur;

// Attribut en sortie
out vec3 couleur_frag;

// Matrices de transformation
uniform mat4 projection;
uniform mat4 vue_modele;

void main() {
    // Calcul de la position finale du sommet
    gl_Position = projection * vue_modele * vec4(sommet, 1.0);
    
    // Transmission de la couleur au fragment shader
    couleur_frag = couleur;
}