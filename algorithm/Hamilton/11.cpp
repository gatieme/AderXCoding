
class MinHamilton
{
	public int getHamiltonPathway(int startPoint, int currentPoint,
			List<Integer> pathway, int[][] distance)
	{
		int totalPoints = distance.length;

		if ( startPoint == currentPoint &&
				isAllVisited(totalPoints, pathway) )
		{
			int currentPathway = getCurrentPathway(pathway, distance);
			if ( currentPathway < minPathway )
			{
				minPathway = currentPathway;
				hasPathway = true;
				bestPathway = new ArrayList<Integer>(pathway);
			}
		}

		for ( int i = 0; i < totalPoints; ++ i )
		{
			if ( i != currentPoint &&
					distance[currentPoint][i] != 0 &&
					!isVisited(startPoint, i, totalPoints, pathway) )
			{
				pathway.add(i);

				if ( getCurrentPathway(pathway, distance) < minPathway )
				{
					getHamiltonPathway(startPoint, i, pathway, distance);
				}
				pathway.remove(pathway.size() - 1);
			}
		}
		return hasPathway ? minPathway : -1;
	}

	public List<Integer> getBestPathway() {
		return bestPathway;
	}

	private boolean isVisited(int startPoint, int currentPoint,
			int totalPoints, List<Integer> pathway) {
		int startPointCounter = 0;
		for ( Integer e : pathway ) {
			if ( e.intValue() == startPoint &&
					pathway.size() == totalPoints &&
					startPointCounter == 0 ) {
				++ startPointCounter;
				continue;
			}
			if ( e.intValue() == currentPoint ) {
				return true;
			}
		}
		return false;
	}

	private boolean isAllVisited(
			int totalPoints, List<Integer> pathway) {
		for ( int i = 0; i < totalPoints; ++ i ) {
			if ( !pathway.contains(i) ) {
				return false;
			}
		}
		return true;
	}

	private int getCurrentPathway(List<Integer> pathway, int[][] distance) {
		if ( pathway.isEmpty() ) {
			return 0;
		}

		int currentPathway = 0;
		for ( int i = 1; i < pathway.size(); ++ i ) {
			int currentPoint = pathway.get(i - 1);
			int nextPoint = pathway.get(i);
			currentPathway += distance[currentPoint][nextPoint];
		}
		return currentPathway;
	}

	private int minPathway = Integer.MAX_VALUE;

	private boolean hasPathway = false;



	List<Integer> bestPathway = null;

	public static void main(String[] args) {

		Scanner in=new Scanner(System.in);
		System.out.println("请输入点级的个数：");
		int n = in.nextInt();

		System.out.println("请输入开始节点：");
		int startPoint = in.nextInt();

		int[][] distance = new int[n][n];
		List<Integer> pathway = new ArrayList<Integer>();
		pathway.add(startPoint);

		for ( int i = 0; i < n; ++ i ) {
			for ( int j = 0; j < i; ++ j ) {
				distance[i][j] = (int)(Math.floor(Math.random() * 100)) + 1;
				distance[j][i] = distance[i][j];
			}
		}
		for ( int i = 0; i < n; ++ i ) {
			for ( int j = 0; j < n; ++ j ) {
				System.out.print(distance[i][j] + " ");
			}
			System.out.println();
		}

		MinHamilton mh = new MinHamilton();
		long startTime = System.currentTimeMillis();
		int minPathway = mh.getHamiltonPathway(startPoint, startPoint, pathway, distance);
		long endTime = System.currentTimeMillis();

		if ( minPathway != -1 ) {
			System.out.println("minPathway = " + minPathway);
			for ( Integer e : mh.getBestPathway() ) {
				System.out.print(e + 1 + " ");
			}
			System.out.println();
		} else {
			System.out.println("No Solution!");
		}
		System.out.println("Total Time: " + (endTime - startTime) + " ms");
	}
}
