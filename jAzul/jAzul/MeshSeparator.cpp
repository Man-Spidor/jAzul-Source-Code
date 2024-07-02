#include "MeshSeparator.h"
#include <assert.h>
#include "Model.h"

// Improtant: the tri index list may be modified (reordered!)
MeshSeparator::MeshSeparator(StandardVertex *pVerts, int nverts, TriangleByIndex*& pTriList, int ntri)
{
	UNREFERENCED_PARAMETER(nverts);

	// create a temporary map to sort the indices
	using KEY = int;
	using MESHINDICES = std::vector<TriangleByIndex>;	
	std::map<KEY, MESHINDICES> meshes;

	// Create the different list of indices for meshes
	for (int i = 0; i < ntri; ++i)
	{
		TriangleByIndex ind = pTriList[i];

		// triangles in one mesh shouldn't share vertices with another mesh
		assert((pVerts[ind.v0].meshnum == pVerts[ind.v1].meshnum) && (pVerts[ind.v0].meshnum == pVerts[ind.v2].meshnum));

		KEY key = (KEY) pVerts[ind.v0].meshnum;
		meshes[key].push_back(ind);
	}

	// we save the mesh count for later validation
	meshcount = (int) meshes.size();

	// Reconsruct a new tri index list ordered by mesh number
	TriangleByIndex* templist = new TriangleByIndex[ntri];
	meshdata = new MeshIndexData[meshes.size()];
	int offsetval = 0;

	int i = 0;
	for (auto it = meshes.begin(); it != meshes.end(); it++)
	{
		meshdata[i].numTri = it->second.size();
		meshdata[i].offset = offsetval;

		// Collect all the tri indices for the i'th mesh
		size_t meshsize = it->second.size();
		for (size_t j = 0; j < meshsize; ++j)
		{
			templist[offsetval + static_cast<int>(j)] = it->second[j];
		}
		
		offsetval += meshes[i].size();
		i++;
	}

	delete[] pTriList;		// Delete the original triangle array
	pTriList = templist;	// Replace it with new re-ordered one

}

MeshSeparator::~MeshSeparator()
{
	delete[] meshdata;
}

void MeshSeparator::GetMeshTriCountAndOffset(int meshnum, int& count, int& offset)
{
	assert((meshnum >= 0) && (meshnum < GetMeshCount()));

	count = meshdata[meshnum].numTri;
	offset = meshdata[meshnum].offset;
}

int MeshSeparator::GetMeshCount()
{
	return meshcount;
}
