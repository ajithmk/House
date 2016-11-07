#include "render.h"
ofstream err("obj_issues.txt");
void objreader(string obj, vector<Vertex>& V, vector<INT32>& I)
{
		char c;
		ifstream is;
		is.open(obj, ios_base::in);
		string temp;
		XMFLOAT4 v; XMFLOAT2 t;
		XMFLOAT3 no;
		struct index { int v_index, t_index, n_index; }ind;
		vector<index> indices1, indices2;
		vector<XMFLOAT4> vertices1, vertices;
		vector<XMFLOAT3> normals1, normals;
		vector<XMFLOAT2> uvs, uvs1;
		while (getline(is, temp))
		{
			istringstream s(temp);
			s >> temp;
			if (temp == "v") { s >> v.x >> v.y >> v.z; v.w = 1; vertices1.push_back(v); }
			if (temp == "vn") { s >> no.x >> no.y >> no.z; normals1.push_back(no); }
			if (temp == "vt") { s >> t.x >> t.y; uvs1.push_back(t); }
			if (temp == "f")
			{
				for (int i = 0; i < 3; i++)
				{
					s >> ind.v_index;
					s.ignore();
					c = s.get();
					if (isdigit(c)) { s.unget(); s >> ind.t_index; s.ignore(); }
					else ind.t_index = 1;
					s >> ind.n_index;
					indices1.push_back(ind);
				}
			}
		}
		int found = 0;
		int size1 = indices1.size();
		for (int i = 0; i < size1; i++)
		{
			found = 0;
			for (int j = i - 1; j >= 0; j--)
			{
				if ((indices1[i].n_index == indices1[j].n_index) && (indices1[i].v_index == indices1[j].v_index) && (indices1[i].t_index == indices1[j].t_index))
				{
					found = 1; break;
				}
			}
			if (found == 0) { indices2.push_back(indices1[i]); }
		}
		int size2 = indices2.size();
		for (int i = 0; i < size2; i++)
		{
			vertices.push_back(vertices1[indices2[i].v_index - 1]);
			normals.push_back(normals1[indices2[i].n_index - 1]);
			if (indices1[i].t_index)uvs.push_back(uvs1[indices2[i].t_index - 1]);
			else uvs.push_back(uvs1[indices2[i].t_index]);
		}
		for (int i = 0; i < size1; i++)
		{
			for (int j = 0; j < indices2.size(); j++)
			{
				if ((indices1[i].n_index != indices2[j].n_index) || ((indices1[i].v_index != indices2[j].v_index) || ((indices1[i].t_index != indices2[j].t_index))))
					continue;
				else
					I.push_back(j);
			}
		}
		Vertex ajith;
		for (int i = 0; i < size2; i++)
		{
			ajith.Pos = vertices[i]; ajith.norm = normals[i]; ajith.tex = uvs[i];
			V.push_back(ajith);
		}
		/*for (int i = 0; i < indices2.size(); i++)
		{
			err << vertices[i].x << "\t" << vertices[i].y << "\t" << vertices[i].z << "\t" << vertices[i].w << "\n";
		}
		err << "\n";
		for (int i = 0; i < indices1.size(); i++)
		{
			err << indices1[i].v_index << "," << indices1[i].t_index << "," << indices1[i].n_index << "\n";
		}
		err << "\n";
		for (int i = 0; i < indices2.size(); i++)
		{
			err << indices2[i].v_index << "," << indices2[i].t_index << "," << indices2[i].n_index << "\n";
		}
		err << "\n";
		for (int i = 0; i < I.size(); i++)
		{
			err << I[i] << "\n";
		}*/
}
void vertexTangentGen(vector<Vertex>& V, vector<INT>& I)
{
	
		unsigned int vertexCount = V.size();
		unsigned int indexCount = I.size();
		XMFLOAT3* tan1 = new XMFLOAT3[vertexCount * 2];
		XMFLOAT3* tan2 = tan1 + vertexCount;
		for (int i = 0; i < indexCount; i = i + 3)
		{
			int i1 = I[i];
			int i2 = I[i + 1];
			int i3 = I[i + 2];

			XMFLOAT4 vertex1 = V[i1].Pos;
			XMFLOAT4 vertex2 = V[i2].Pos;
			XMFLOAT4 vertex3 = V[i3].Pos;
			XMFLOAT2 texcoord1 = V[i1].tex;
			XMFLOAT2 texcoord2 = V[i2].tex;
			XMFLOAT2 texcoord3 = V[i3].tex;

			float x1 = vertex2.x - vertex1.x;
			float x2 = vertex3.x - vertex1.x;
			float y1 = vertex2.y - vertex1.y;
			float y2 = vertex3.y - vertex1.y;
			float z1 = vertex2.z - vertex1.z;
			float z2 = vertex3.z - vertex1.z;

			float s1 = texcoord2.x - texcoord1.x;
			float s2 = texcoord3.x - texcoord1.x;
			float t1 = texcoord2.y - texcoord1.y;
			float t2 = texcoord3.y - texcoord1.y;

			float r = 1.0f / (s1*t2 - s2*t1);
			XMFLOAT3 sdir((t2*x1 - t1*x2)*r, (t2*y1 - t1*y2)*r, (t2*z1 - t1*z2)*r);
			XMFLOAT3 tdir((s1*x2 - s2*x1)*r, (s1*y2 - s2*y1)*r, (s1*z2 - s2*z1)*r);

			tan1[i1].x = tan1[i1].x + sdir.x; tan1[i1].y = tan1[i1].y + sdir.y; tan1[i1].z = tan1[i1].z + sdir.z;
			tan1[i2].x = tan1[i2].x + sdir.x; tan1[i2].y = tan1[i2].y + sdir.y; tan1[i2].z = tan1[i2].z + sdir.z;
			tan1[i3].x = tan1[i3].x + sdir.x; tan1[i3].y = tan1[i3].y + sdir.y; tan1[i3].z = tan1[i3].z + sdir.z;
			tan2[i1].x = tan2[i1].x + tdir.x; tan2[i1].y = tan2[i1].y + tdir.y; tan2[i1].z = tan2[i1].z + tdir.z;
			tan2[i2].x = tan2[i2].x + tdir.x; tan2[i2].y = tan2[i2].y + tdir.y; tan2[i2].z = tan2[i2].z + tdir.z;
			tan2[i3].x = tan2[i3].x + tdir.x; tan2[i3].y = tan2[i3].y + tdir.y; tan2[i3].z = tan2[i3].z + tdir.z;
		}
		for (int i = 0; i < vertexCount; i++)
		{
			XMVECTOR n = XMLoadFloat3(&V[i].norm);
			XMVECTOR t = XMLoadFloat3(&tan1[i]);
			XMFLOAT3 temp;
			XMStoreFloat3(&temp, XMVector3Normalize(t - n*XMVector3Dot(n, t)));
			float s;
			XMStoreFloat(&s, XMVector3Dot(XMVector3Cross(n, t), XMLoadFloat3(&tan2[i])));
			V[i].tangent.x = temp.x; V[i].tangent.y = temp.y; V[i].tangent.z = temp.z;
			V[i].tangent.w = (s > 0.0f) ? -1.0f : 1.0f;
		}
		delete[] tan1;
		/*for (int i = 0; i < vertexCount; i++)
		{
			err << V[i].tangent.x << " " << V[i].tangent.y << " " << V[i].tangent.z << " " << V[i].tangent.w << "\n";
		}
		err << "One object done\n" << endl;*/
	
}