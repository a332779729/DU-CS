import java.util.LinkedList;
import java.util.Scanner;

public class test {
	
	public class Vertex {
	    private int value;
		private Vertex parent;
	    private LinkedList<Vertex> neighbors;
	    
	    public Vertex(Vertex neighbor, Vertex parent) {
	    		this.parent = parent;
	    		this.neighbors.add(neighbor);
	    }
	    
	    public String getNeighbors() {
	    		return neighbors.toString();
	    }
	    
	    public Vertex getParent() {
    		return parent;
	    }
	}
	
	public class Edge {
		private Vertex v1;
		private Vertex v2;
		private int weight;
		
		public Edge(int weight) {
			this.v1 = v1;
			this.v2 = v2;
			this.weight  = weight;
		}
		
		public Edge(Vertex v1, Vertex v2, int weight) {
			this.v1 = v1;
			this.v2 = v2;
			this.weight  = weight;
		}
		
		public int getV1() {
			return v1.value;
		}
		
		public int getV2() {
			return v2.value;
		}
		
		public int weight(Vertex v1, Vertex v2) {
			return weight;
		}
		
		public String toString() {
			String str = "[" + v1 +", " + v2 + ", " + weight + "]";
			return str;
		}
	}
	
	public class Graph{
		private int vNum;
		private int edgeNum;
		private LinkedList<Edge>[] edgeLinks;
		private LinkedList<Vertex> viewed;
		private LinkedList<Integer> edgeC;
		
		public Graph(int vNum) {
			this.vNum = vNum;
			this.edgeNum = 0;
			this.edgeLinks = new LinkedList[vNum];
			for(int i = 0;i<vNum;i++) {
				edgeLinks[i] = new LinkedList<>();
			}
		}
		
		public void Prime(Vertex source) {
			viewed = new LinkedList<>();
			edgeC = new LinkedList<>();
			
			viewed.add(source);
			edgeC.add(source.value, 0);
			
			while(viewed.size() < vNum){
				//compare viewed's neighbors
				Vertex head = viewed.get(0);
				viewed.add(minCost(head));
				}
		
	}
		public Vertex minCost(Vertex a) {
			Vertex v = a;
			int cost = Edge.weight(v, v.getNeighbors());
			
			return cost;
		}

	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}

}
