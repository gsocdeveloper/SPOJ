#include <cstdio>
#include <cstring>

#define LEFT(n) ( (n << 1) )
#define RIGHT(n) ( (n << 1)|1 )
#define max(a, b) (a > b ? a : b)

const int MAX_N = 3e5 + 5;
long long sum_tree[3*MAX_N];
long long max_tree[3*MAX_N];
long long A[MAX_N];

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

long long square(long long n)
{
    return n*n;
}

long long square_root(long long n)
{
    long long left = 1, right = 1e9;

    while(left <= right)
    {
        long long mid = (left + right) >> 1;

        if(square(mid) <= n)
        {
            if(square(mid + 1) > n)
            {
                return mid;
            }
            else
            {
                left = mid + 1;
            }
        }
        else
        {
            right = mid;
        }
    }
}

void build(int n, int left, int right)
{
    if(left == right)
    {
        sum_tree[n] = max_tree[n] = A[left];
        return;
    }

    int mid = (left + right) >> 1;
    build(LEFT(n), left, mid);
    build(RIGHT(n), mid + 1, right);

    max_tree[n] = max(max_tree[LEFT(n)], max_tree[RIGHT(n)]);
    sum_tree[n] = sum_tree[LEFT(n)] + sum_tree[RIGHT(n)];
}

void update(int n, int left, int right, int query_left, int query_right)
{
    if(query_right < left || right < query_left || max_tree[n] == 1)
        return;

    if(left == right)
    {
        A[left] = square_root(A[left]);
        sum_tree[n] = max_tree[n] = A[left]; //printf("A[%d] is now %lld\n", left, A[left]);
        return;
    }

    int mid = (left + right) >> 1;
    update(LEFT(n), left, mid, query_left, query_right);
    update(RIGHT(n), mid + 1, right, query_left, query_right);

    sum_tree[n] = sum_tree[LEFT(n)] + sum_tree[RIGHT(n)];
    max_tree[n] = max(max_tree[LEFT(n)], max_tree[RIGHT(n)]); //printf("S[%d] = %lld\n", n, sum_tree[n]);
}

long long sum(int n, int left, int right, int query_left, int query_right)
{
    if(query_right < left || right < query_left)
        return 0;

    if(query_left <= left && right <= query_right)
        return sum_tree[n];

    int mid = (left + right) >> 1;
    long long left_sum = sum(LEFT(n), left, mid, query_left, query_right);
    long long right_sum = sum(RIGHT(n), mid + 1, right, query_left, query_right);

    return (left_sum + right_sum);
}

void solve(int no_of_elements)
{
    for(int i = 1; i <= no_of_elements; i++)
        scanf("%lld", &A[i]);

    memset(max_tree, 0, sizeof(max_tree));
    memset(sum_tree, 0, sizeof(sum_tree));
    build(1, 1, no_of_elements);

    int no_of_queries;
    scanf("%d", &no_of_queries);

    while(no_of_queries--)
    {
        const int SUM = 1, UPDATE = 0;
        int query_type, left, right;
        scanf("%d %d %d", &query_type, &left, &right);

        if(left > right) swap(left, right);

        if(query_type == SUM)
        {
            long long answer_sum = sum(1, 1, no_of_elements, left, right);
            printf("%lld\n", answer_sum);
        }
        if(query_type == UPDATE)
        {
            update(1, 1, no_of_elements, left, right);
        }
    }
    printf("\n");
}

int main()
{
    for(int i = 1; ; i++)
    {
        int no_of_elements;

        if(scanf("%d", &no_of_elements) < 1)
            break;

        printf("Case #%d:\n", i);
        solve(no_of_elements);
    }

    return 0;
}
