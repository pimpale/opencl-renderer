//Convert cells of .off format to vram memory buffers

//3d plane object
struct plane_3d {
	float3 norm;
	float3 cntr;
}



struct face { //faces exist in 3d space
	float3 vertices[3];	
	struct plane_3d p;
	float4 rotation_matrix	
	struct cell* c1;
	struct cell* c2;
}

//tetrahedronal cell (3d space)
struct cell {

	struct face[4] f;
}


void get_tri_plane(struct plane *r, float3 *v1, float3* v2, float3* v3) 
{

}

//Less than 65,535 vertices
//All cells must be tetrahedrons, all faces triangles

void kernel initvertex(
		const unsigned short vertice_num,
		const unsigned short face_num;
		const unsigned short cell_num;
		const float4*          vertices     //
		const unsigned short4* face_indices //
		const unsigned short4* cell_indices //
		
		struct face* out_faces  
		struct cell* out_cells   
		)
{
	//id is the cell number
	//initialize cell struct
	
	//initialize 4 faces, place inside cell
	//for each face
	//	find all other cuboids with this face	
	//	rotate it to a 2d state
	
	   
	
}
