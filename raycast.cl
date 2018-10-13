#define EPSILON 0.0001f

struct face {
	float4 v0;
	float4 v1;
	float4 v2;

	float4 plane_normal;
};

struct tetrahedron {
	struct face f[4];
};

//gets normal of a triangle
float4 get_normal(const struct face* f)
{
	//cross of the two sides
	float4 vSide1 = f->v0 - f->v1;
	float4 vSide2 = f->v0 - f->v2;

	return cross(vSide1, vSide2);	
}

//the magic of weird math that i got from online 
bool plane_collision( 
		const float4 *plane_center, const float4 *plane_normal, 
		const float4 *ray_location, const float4 *ray_vector,
		float *t)
{
	float denominator = dot(*ray_vector,*plane_normal);
	if(fabs(denominator) > EPSILON)
	{
		*t = dot(*plane_center - *ray_location, *plane_normal) / denominator;
		if(*t >= 0)
		{
			return true;
		}
	}
	return false;
}
/* Precondition: The vector origin must be within the tetrahedron
 * Args:
 * Returns: The index of the face that was collided with
 */
int get_face_collided(struct tetrahedron* this_tet,
                      float4*			  ray_location,
                      float4* 			  ray_vector)
{
	//t is sort of like distance. It is proportional	
	float t_of_faces[4];
	
	//test all faces	
	for(int i = 0; i < 4; i++)
	{		
		struct face f = this_tet->f[0];
		//get collision point with plane		
		if(!plane_collision(&f.v0, &f.plane_normal, 
						ray_location, ray_vector,
						&t_of_faces[i]))
		{
			//if it doesn't collide, then set distance to
			t_of_faces[i] = 50000;//set to an arbitrary positive amount
		}
	}
	//get smallest index in array (closest of all in the list)
	int index_of_smallest_t;
	for(int i = 0; i < 4; i++)
	{
		if(t_of_faces[i] < t_of_faces[index_of_smallest_t])
		{
			index_of_smallest_t = i;
		}
	}
	return index_of_smallest_t;
}


/* Precondition 
 *
 */
//void jumpTriangle(Face

void kernel raycast(

//	global const struct tetrahedron* cells,
//	global const struct triangle*    faces,


	global const float4* location, 
	global const float4* vector, 
	global unsigned int* color)
{
	int id = get_global_id(0);
	float4 loc = location[id];
	float4 vec = vector[id];
	
	color[id] = 0;
	
	int dist = 0;
	
	for(int i = 0; i < 255; i++)
	{
		loc += vec;
		dist++;
		if(loc.x > -5 && loc.x < 5 && loc.y > -5 && loc.y < 5 && loc.z > -5 && loc.z < 5)
		{
			color[id] = 0x0000FF - dist;
			break;
		}

		if(loc.z > 10)
		{
			loc.z -= 20;
		}
		else if(loc.z < -10)
		{
			loc.z += 20;
		}

		if(loc.y > 10)
		{
			loc.y -= 20;
		}
		else if(loc.y < -10)
		{
			loc.y += 20;
		}

		if(loc.x > 10)
		{
			loc.x -= 20;
		}
		else if(loc.x < -10)
		{
			loc.x += 20;
		}

	}
}
