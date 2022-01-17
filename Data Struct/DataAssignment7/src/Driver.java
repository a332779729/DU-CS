import java.io.File;
import java.util.LinkedList;
import java.util.Scanner;

public class Driver {
	
	public static LinkedList<LinkedList<Integer>> Input(String filepath) {
		File inFile = new File(filepath);
		LinkedList<LinkedList<Integer>> input= new LinkedList<>();
		try {
			Scanner scanner = new Scanner(inFile);
			int n = scanner.nextInt();
			//input 
			for(int i= 0; i< n; i++) {
				LinkedList<Integer> ls = new LinkedList<>();
				input.add(ls);
			}
			while(scanner.hasNext()) {
				int v1 = scanner.nextInt();
				int v2 = scanner.nextInt();
				int weight = scanner.nextInt();
				
				input.get(v1).add(v2);
				input.get(v1).add(weight);
				input.get(v2).add(v1);
				input.get(v2).add(weight);
			}
		}
		catch(Exception e) {
			
		}
		return input;
		
	}
	
	public static void prim(LinkedList<LinkedList<Integer>> input , int source) {
		LinkedList<Integer> cost = new LinkedList<>();
		LinkedList<Integer> parent = new LinkedList<>();
		LinkedList<Integer> viewed = new LinkedList<>();
		
		for(int i=0; i<input.size(); i++ ) {
			cost.add(Integer.MAX_VALUE);
			parent.add(-1);
		}
		cost.set(source, 0);
		
		while(viewed.size() < input.size()) {
			// find min
			int minCost = Integer.MAX_VALUE;
			int minV = -1;
			for(int i = 0; i < cost.size(); i++) {
				if(!viewed.contains(i) && minCost > cost.get(i)) {
					minCost = cost.get(i);
					minV = i;
				}
			}
			// view
			viewed.add(minV);
			// update neighbor
			LinkedList<Integer> smallList = input.get(minV);
			for(int i = 0; i < smallList.size(); i += 2) {
				int neighbor = smallList.get(i);
				int weight = smallList.get(i+1);
				if(!viewed.contains(neighbor) && cost.get(neighbor) > weight) {
					cost.set(neighbor, weight);
					parent.set(neighbor, minV);
				}
			}
		}
		
		int sumCost = 0;
		for(int i=0; i< input.size(); i++) {
			System.out.println(i + " " + cost.get(i) + " " + parent.get(i));
			sumCost += cost.get(i);
		}
		System.out.println(sumCost);
	}
	
	

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		LinkedList<LinkedList<Integer>> graph = Input(args[0]);
		
		prim(graph, Integer.parseInt(args[1]));

	}

}
