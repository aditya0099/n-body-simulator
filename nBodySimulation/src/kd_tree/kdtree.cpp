/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <cmath>

using namespace std;

/** Determines if Point a is smaller than Point b in a given dimension d. */
template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    const double f = first[curDim];
    const double s = second[curDim];

    if (f < s)
    {
        return true;
    }
    else if (s < f)
    {
        return false;
    } 
    else
    {
        return first < second;
    }
}

/** Determines if a Point is closer to the target Point than another
 * reference Point. Takes three points: target, currentBest, and
 * potential, and returns whether or not potential is closer to
 * target than currentBest.
 */
template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    double potentialDist = getDistSquared(potential, target);
    double currentBestDist = getDistSquared(currentBest, target);

    if (potentialDist < currentBestDist)
    {
        return true;
    }
    else if (currentBestDist < potentialDist)
    {
        return false;
    }
    else
    {
        return potential < currentBest;
    }
}


/** Helper function to calculate the squared euclidian distnace between two points */
template <int Dim>
double KDTree<Dim>::getDistSquared(const Point<Dim>& p1, const Point<Dim>& p2) const {
    double dist = 0;
    for (int k = 0; k < Dim; k++)
    {
        dist += std::pow(p1[k] - p2[k], 2);
    }
    return dist;
}

/** Constructs a KDTree with the provided points */
template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    if (newPoints.empty())
    {
        root = NULL;
        size = 0;
    }
    else
    {   
        vector<Point<Dim> > points = newPoints;
        root = constructTree(newPoints, 0, newPoints.size() - 1, 0);
        size = newPoints.size();
    }
}

/** Copy constructor for the KDTree */
template <int Dim>
KDTree<Dim>::KDTree(const KDTree& other)
{
  /**
   * @todo Implement this function!
   */
  _copy(other);
}

/** Copies another tree into the current tree */
template <int Dim>
void KDTree<Dim>::_copy(const KDTree& other)
{
    root = _copyTree(other.root);
    size = other.size;    
}

/** Recursive helper function for copying the tree */
template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::_copyTree(KDTreeNode* subroot) 
{
    if (subroot == NULL)
    {
        return NULL;
    }

    KDTreeNode* new_subroot = new KDTreeNode(subroot->point);

    new_subroot->left = _copyTree(subroot->left);
    new_subroot->right = _copyTree(subroot->right);

    return new_subroot;
}


/** Recursive helper function for constructing a KDTree */
template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::constructTree(vector<Point<Dim> > points, int lo, int hi, int d)
{
    if (lo > hi || hi < lo)
    {
        return NULL;
    }

    int point = quickSelect(lo, hi, d, points, (hi + lo)/2);

    KDTreeNode* subroot = new KDTreeNode(points[point]);
    
    d = (d + 1) % Dim;
    
    subroot->left = constructTree(points, lo, point - 1, d);
    subroot->right = constructTree(points, point + 1, hi, d);

    return subroot;
}

/** Selects the m-th smallest point from a vector of points */
template <int Dim>
int KDTree<Dim>::quickSelect(int lo, int hi, int d, vector<Point<Dim> > &data, int m)
{
    if (lo == hi) 
    {
        return lo;
    } 

    // Move the pivot to the end and partition
    int pivot_idx = (lo + hi) / 2;
    std::swap(data[pivot_idx], data[hi]);
    pivot_idx = partition(data, lo, hi, d);

    // If the pivot is in the median position, then we are done
    if (pivot_idx == m)
    {
        return pivot_idx;
    }
    // Otherwise, recurse until we reach the median location
    else if (pivot_idx > m)
    {
        return quickSelect(lo, pivot_idx - 1, d, data, m);
    }
    else
    {
        return quickSelect(pivot_idx + 1, hi, d, data, m);
    }
}

/** Helper function for quickselect, partitions the data based on the last element */
template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim> > &data, int lo, int hi, int d)
{
    // Get pivot value
    Point<Dim> pivot = data[hi];
    int writePos = lo;

    // Loop and swap small items to the front
    for (int i = lo; i < hi; i++)
    {
        if (smallerDimVal(data[i], pivot, d))
        {
            std::swap(data[i], data[writePos]);
            writePos++;
        }
    }

    // Place pivot in the correct location
    std::swap(data[writePos], data[hi]);
    return writePos;
}

/** Assignment operator for the KDTree; makes a deep copy */
template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree& rhs) {
  /**
   * @todo Implement this function!
   */

  if (&rhs != this)
  {
      _clear(root);
      _copy(rhs);
  }

  return *this;
}

/** Destructor for the KDTree; deletes all nodes */
template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
    _clear(root);
}

/** Resursive helper function to delete all nodes of a tree */
template <int Dim>
void KDTree<Dim>::_clear(KDTreeNode* subroot)
{
    if (subroot == NULL)
    {
        return;
    }

    _clear(subroot->left);
    _clear(subroot->right);
    delete subroot;
}

/** Finds the closest point to the parameter point in the KDTree.*/
template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    return findNearestNeighbor(query, 0, root)->point;
}

/** Recurisve helper function to find the nearest neighbor point to the query */
template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query,
    int d, KDTreeNode* subroot) const
{
    typename KDTree<Dim>::KDTreeNode* currentBest = NULL;

    // Stores the node that is not visited
    KDTreeNode* other = NULL;

    // Base case, return self if leaf
    if (subroot == NULL)
    {
        return subroot;
    }

    // Decide whether to recurse left or right depending on the current subdivision
    if (smallerDimVal(query, subroot->point, d))
    {
        // Recurse and update if the subchild point is better
        currentBest = findNearestNeighbor(query, (d + 1) % Dim, subroot->left);
        other = subroot->right;
    }
    else
    {
        // Recurse and update if the subchild point is better
        currentBest = findNearestNeighbor(query, (d + 1) % Dim, subroot->right);
        other = subroot->left;
    }

    // Update if the subchild is better
    if (currentBest == NULL || shouldReplace(query, currentBest->point, subroot->point))
    {
        currentBest = subroot;
    }

    // Get's the current best radius
    int rSq = getDistSquared(currentBest->point, query);

    typename KDTree<Dim>::KDTreeNode* potential = NULL;

    // If this radius extends into the other plane, recurse further
    if (other != NULL && std::pow(query[d] - subroot->point[d], 2) <= rSq) {
        potential = findNearestNeighbor(query, (d + 1) % Dim, other);

        if (shouldReplace(query, currentBest->point, potential->point))
        {
            currentBest = potential;
        }
    }
    
    return currentBest;
}
