import argparse


def readInput():
    input_vectors = []
    while True:
        vec = []
        try:
            for num in input().split(','):
                num_r = float(format(float(num), '.4f'))
                vec.append((num_r))
            input_vectors.append(vec)
        except EOFError:
            break
    return input_vectors


def calcDis(v1, v2):
    res = 0
    d = len(v1)
    for i in range(d):
        res += (v1[i] - v2[i]) ** 2
    return res


def addVectors(v1, v2):
    vector = []
    d = len(v1)
    for i in range(d):
        vector.append(v1[i] + v2[i])
    return vector


def calcCentroids(vector, t):
    d = len(vector)
    for i in range(d):
        vector[i] = vector[i] / t
    return vector


def kmeans(k, maxiter=200):
    iters = 0
    vectors = readInput()
    centroids = []

    n = len(vectors)
    d = len(vectors[0])

    if (k >= n):
        print("invalid inputs")
        exit()

    for i in range(k):  # init centroids list
        centroids.append(vectors[i].copy())

    flag = True
    while iters <= 200 and flag:
        groups = [[] for i in range(k)]
        n = len(vectors)
        iters += 1

        for i in range(n):  # creatse Si groups , iterate over vectors list
            index = 0
            curr_dis = calcDis(vectors[i], centroids[0])
            for j in range(1, k):  # iterating centroids list
                new_dis = calcDis(vectors[i], centroids[j])
                if new_dis <= curr_dis:
                    curr_dis = new_dis
                    index = j
            groups[index].append(vectors[i])

        new_centroids = [[] for i in range(k)]
        for j in range(len(groups)):  # create new centroids list
            for i in range(len(groups[j]) - 1):
                groups[j][0] = addVectors(groups[j][0], groups[j][i + 1])
            new_centroids[j] = calcCentroids(groups[j][0], len(groups[j]))

        cnt = 0
        for i in range(k):  # update centroids list with new centroids
            if (centroids[i] != new_centroids[i]):
                centroids[i] = new_centroids[i]
                cnt += 1
        if (cnt == 0):
            flag = False

    final_centroids = [[0 for j in range(d)] for i in range(k)]
    for i in range(k):
        for j in range(d):
            final_centroids[i][j] = ('{:.4f}'.format(centroids[i][j]))
        print(*final_centroids[i], sep=", ")


parser = argparse.ArgumentParser()
parser.add_argument('k', type=int)
parser.add_argument('maxiter', nargs='?', const=1, type=int, default=200)
args = parser.parse_args()

kmeans(args.k, args.maxiter)