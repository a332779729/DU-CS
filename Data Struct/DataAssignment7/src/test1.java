import java.io.File;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;
import java.util.Set;

import test.Vertex;

public class test1 {
	
	//input
	public static List<Set<Integer>> readGraphFromFile(String filepath){
        File inFile = new File(filepath);
        try {
            Scanner scanner = new Scanner(inFile);
            int n = scanner.nextInt();
            List<Set<Integer>> result = new ArrayList<>(n);
            for(int i = 0; i < n; i++)  result.add(new HashSet<Integer>());
            while(scanner.hasNext()){
                int i = scanner.nextInt();
                int j = scanner.nextInt();
                result.get(i).add(j);
                result.get(j).add(i);
            }
            return result;
        }
        catch(Exception e){
            return null;
        }
    }
	
	
	//prime 
	public static int primeSpenningTree(Vertex source, int numVertx){
		LinkedList<Vertex> viewed = new LinkedList<>();
		LinkedList<Integer> cost = new LinkedList<>();
		LinkedList<Integer> parent = new LinkedList<>();
		
		//viewed
		viewed.add(source);
		
		//cost
		for(int i=0; i< numVertx; i++) {
			cost.add(i, Integer.MAX_VALUE);
		}
		
		//parent
		for(int i=0; i<numVertx; i++) {
			parent.add(i);
		}
		
		//loop
		while(viewed.size() < numVertx) {
			
			int minCost;
			Vertex minV;
			for(int i= 0; i< cost.size(); i++) {
				int currCost = cost.get(i);
				
			}
			
			Vertex head = viewed.get(0);
			LinkedList<Vertex> neighbors = head.getNeighbors();
			for(int i=0; i < neighbors.size(); i++) {
				int neighbor = neighbors.get(i);
				if(neighbor.weight >= cost.get(neighbor)) {
					continue;
				}else {
					cost.set(neighbor, neighbor.weight);
					viewed.add(neighbor);
					parent.set(neighbor, head);
				}				
			}
		}
		
		 
		 return -1;
		 
	 }
	
	public class Vertex{
		private int value;
		private Vertex parent;
		private Vertex neighbor;
		private LinkedList<Vertex> Neighbors;
		
		public Vertex(int v) {
			this.value = v; 
		}
		
		public LinkedList<Vertex> getNeighbors() {
			return null;
		}

		public Vertex(int v, Vertex parent) {
			this.value = v; 
			this.parent = parent;
		}
		
		public Vertex(int v, Vertex parent, Vertex neighbor) {
			this.value = v; 
			this.parent = parent;
			this.neighbor = neighbor;
		}
		
		//?
		public int getMinEdge() {
			
			return minEdge;
		}
		
		public void addParentValue(Vertex v, int p) {
			v.parent.value = p;
		}
		
		public int getParentValue() {
			return parent.value;
		}
	}

	
	//main
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner in = new Scanner(System.in);
		int n, m, weight;
		int sum; 			//sum of weight
		boolean[] isViewed; //if the vertexes be connected, it is be true;
		int[][] vertx;
		int[] dis;
		
		n = in.nextInt();
		m = in.nextInt();
		vertx = new int[n][n];
		isViewed = new boolean[n];
		dis = new int[n];
		
		

	}

}
