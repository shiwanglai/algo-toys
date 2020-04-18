#include <stdio.h>

#define GRID_ROWS    100
#define GRID_COLS    100

/*
 * function divide and conquer
 *
 *   *----*----*----*
 *   |    |    |    |
 *   *----*----*----$
 *   |    |    |    |
 *   *----*----@----#
 *
 * Ways to # equal to the ways to @ plus ways to $.
 * Below is the described formula.
 * f(x, y) = f(x - 1, y) + f(x, y - 1)
 */
int f_dc(int x, int y)
{
    /* check validity */
    if (x < 0 || y < 0)
        return 0;

    /* over, the start point */
    if (x == 0 && y == 0)
        return 1;

    return f_dc(x - 1, y) + f_dc(x, y - 1);
}

/*
 * function dynamic programming
 *
 *   !----$----*----*
 *   |    |    |    |
 *   @----#----*----*
 *   |    |    |    |
 *   *----*----*----*
 *
 * Ways to ! is 1, the start point.
 * Ways to $ is 1.
 * Ways to @ is 1.
 * Ways to # is 2, which is the ways to @ plus ways to $.
 * And so on.
 * f(x, y) = f(x - 1, y) + f(x, y - 1)
 */
#define DP_ROWS    100
#define DP_COLS    100
static int dp[DP_ROWS][DP_COLS];
int f_dp(int x, int y)
{
    /* init the start point */
    dp[0][0] = 1;

    /* init the 1st column */
    for (int i = 0; i <= x; i++) {
        dp[i][0] = 1;
    }

    /* init the 1st row */
    for (int j = 0; j <= y; j++) {
        dp[0][j] = 1;
    }

    /* calc from the point (1, 1) */
    for (int i = 1; i <= x; i++) {
        for (int j = 1; j <= y; j++) {
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
    }

    return dp[x][y];
}

static int count;
/*
 * function divide and conquer with count
 * no other diffs compared to f_dc
 * you can also run "time ./a.out" to get the time cost
 *
 *   *----*----*----*
 *   |    |    |    |
 *   *----*----*----$
 *   |    |    |    |
 *   *----*----@----#
 *
 * Ways to # equal to the ways to @ plus ways to $.
 * Below is the described formula.
 * f(x, y) = f(x - 1, y) + f(x, y - 1)
 */
int f_dc_count(int x, int y)
{
    count++;

    /* check validity */
    if (x < 0 || y < 0)
        return 0;

    /* over, the start point */
    if (x == 0 && y == 0)
        return 1;

    return f_dc_count(x - 1, y) + f_dc_count(x, y - 1);
}

static int count_cache;
/*
 * function divide and conquer with cache
 *
 *   *----*----*----*
 *   |    |    |    |
 *   *----*----*----$
 *   |    |    |    |
 *   *----*----@----#
 *
 * Ways to # equal to the ways to @ plus ways to $.
 * Below is the described formula.
 * f(x, y) = f(x - 1, y) + f(x, y - 1)
 */
#define CACHE_ROWS    100
#define CACHE_COLS    100
static int cache[CACHE_ROWS][CACHE_COLS];
int f_dc_cache(int x, int y)
{
    count_cache++;

    /* check validity */
    if (x < 0 || y < 0)
        return 0;

    /* over, the start point */
    if (x == 0 && y == 0)
        return 1;

    if (cache[x][y] != 0) {
        return cache[x][y];
    }

    cache[x][y] = f_dc_cache(x - 1, y) + f_dc_cache(x, y - 1);
    return cache[x][y];
}

/*
 * dfs, depth first search
 *
 * It's a way of step and options.
 * The step is a step in depth.
 * The options is the choices after the step.
 * Commonly there are 4 options, namely 4 directions(right/down/left/up).
 *
 * Different from the former topic, which always asked a nearest way,
 * this topic only requests that you not go the same node.
 * A kidding saying is to send a fairy home :)
 *
 * We defined a step function which return the number of ways home.
 * The parameter x, y is start points.
 * The parameter tx, ty is the home/target point.
 *
 *   0    1    2    3
 * 0 %----$----*----*
 *   |    |    |    |
 * 1 @----*----*----*
 *   |    |    |    |
 * 2 *----*----*----#
 *
 * The start point is %, target is #
 * A first step is to %, its options is $ and @
 */
static int visited[GRID_ROWS][GRID_COLS];
int step(int x, int y, int tx, int ty)
{
	/*
	 * match
	 */
	if (x == tx && y == ty) {
		/* reach the target, one way */
		return 1;
	}

	/*
	 * out of bounds
	 */
	if (x < 0 || y < 0 || x > tx || y > ty) {
		/* out of the scope, no way */
		return 0;
	}

	/*
	 * options
	 */

	/* check visted */
	if (visited[x][y]) {
		/* it's a rule, no visit a node twice */
		return 0;
	}

	/* tag visited */
	visited[x][y] = 1;

	int sum = 0;
	sum += step(x + 1, y, tx, ty); /* right */
	sum += step(x, y + 1, tx, ty); /* down */
	sum += step(x - 1, y, tx, ty); /* left */
	sum += step(x, y - 1, tx, ty); /* up */

	/* 4 directions finished, we've gone all the ways here
	 * maybe we've reach the target
	 * maybe not, however now we should leave the node */
	visited[x][y] = 0;

	return sum;
}

int main()
{
    int x = 4; //15;
    int y = 3; //14;
 
    printf("f_dc(%d, %d) = %d\n", x, y, f_dc(x, y));
    printf("f_dp(%d, %d) = %d\n", x, y, f_dp(x, y));

    count = 0;
    printf("f_dc_count(%d, %d) = %d\n", x, y, f_dc_count(x, y));
    printf("f_dc_count(%d, %d) count = %d\n", x, y, count);
    count_cache = 0;
    printf("f_dc_cache(%d, %d) = %d\n", x, y, f_dc_cache(x, y));
    printf("f_dc_cache(%d, %d) count = %d\n", x, y, count_cache);

    /* dfs */
    int sx = 0, sy = 0; /* start */
    int tx = 2, ty = 2; /* target 2,2 is 12 ways */
    printf("step(%d, %d, %d, %d) = %d\n", sx, sy, tx, ty, step(sx, sy, tx, ty));

    return 0;
}
