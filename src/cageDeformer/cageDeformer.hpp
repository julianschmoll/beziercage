#pragma once

#include <array>
#include <maya/MDataBlock.h>
#include <maya/MItGeometry.h>
#include <maya/MMatrix.h>
#include <maya/MObject.h>
#include <maya/MPlug.h>
#include <maya/MPoint.h>
#include <maya/MPointArray.h>
#include <maya/MPxDeformerNode.h>
#include <maya/MThreadPool.h>
#include <maya/MTypeId.h>
#include <maya/MVector.h>
#include <vector>

enum class DeformState { PreDeform, PostDeform };

// This struct holds the data for each deform task.
struct deformTaskData {
    unsigned int numVerts;
    MPointArray *points;
    const std::vector<float> *bindDistance;
    const std::vector<float> *weights;
    float envelope;
    float distanceTreshold;
    const std::vector<std::vector<MPoint>> *controlPoints;
    const std::vector<std::vector<MPoint>> *preControlPoints;
    const std::vector<unsigned int> *patchIndex;
    const std::vector<float> *u;
    const std::vector<float> *v;
    const MMatrix *localToWorldMatrix;
    const MMatrix *worldToLocalMatrix;
};

// This struct holds the data for each thread in the deform task.
struct deformThreadData {
    unsigned int start, end, numTasks;
    deformTaskData *data;
};

class bezierCage : public MPxDeformerNode {
public:
    bezierCage();

    ~bezierCage() override = default;

    static void *creator();

    static MStatus initialize();

    MStatus deform(MDataBlock &dataBlock, MItGeometry &geometryIterator, const MMatrix &localToWorldMatrix, unsigned int geometryIndex) override;

    static MTypeId id;
    static const char *typeName;

    // Node attributes
    static MObject aControlMessage;
    static MObject aPatchMatrices;
    static MObject aMatrix;
    static MObject aBindPreMatrix;
    static MObject aPatchBindPreMatrices;
    static MObject aThreshDist;
    static MObject aBindUV;
    static MObject aBindDistance;
    static MObject aBindPatchIndex;
    static MObject aVertexBindPosition;
    static MObject aVertexBindData;
    static MObject aGeometryBindData;
    static MObject aDirty;

    std::vector<deformThreadData> MDeformThreadData;
    deformTaskData MDeformTaskData;

private:
    /**
     * Creates thread data for parallel processing.
     */
    void CreateThreadData();

    /**
     * Matches the length of bind pre matrices array to the patch matrices array.
     * @param[in,out] dataBlock The data block of the deformer.
     * @return MStatus indicating success or failure.
     */
    static MStatus updateBindPreMatrixPlugs(MDataBlock &dataBlock);

    /**
     * Retrieves the control points for all Bézier patches from the given data block.
     * @param[in, out] dataBlock The data block of the deformer.
     * @param preDeform If true, retrieves pre-deformation control points.
     * @return A vector of vectors containing control points for each Bézier patch.
     */
    static std::vector<std::vector<MPoint>> getControlPoints(MDataBlock &dataBlock, DeformState state);

    /**
     * Creates thread tasks for parallel region execution.
     * @param[in] pData Pointer to the thread data array.
     * @param[in] pRoot Pointer to the root task for the thread pool.
     */
    static void CreateTasks(void *pData, MThreadRootTask *pRoot);

    /**
     * Evaluates the deformation for a given thread's data range.
     * @param[in] pParam Pointer to the thread's data.
     * @return MThreadRetVal Return value for the thread pool.
     */
    static MThreadRetVal ThreadEvaluate(void *pParam);

    /**
     * Binds the geometry to the cage.
     * @param[in,out] dataBlock The data block of the deformer.
     * @param[in,out] geometryIterator The geometry iterator for the deformed geometry.
     * @param[in] localToWorldMatrix The local to world matrix for the geometry.
     * @param[in] geometryIndex The index of the geometry being deformed.
     * @return MStatus indicating success or failure.
     */
    static MStatus bind(MDataBlock &dataBlock, MItGeometry &geometryIterator, const MMatrix &localToWorldMatrix, unsigned int geometryIndex);

    /**
     * Calculates the binding for a specific point.
     * @param[in,out] controlPoints The control points of the Bézier patches.
     * @param[in] queryPoint The point for which the binding is calculated.
     * @return An array containing the UV coordinates of the binding point in the patch.
     */
    static std::array<float, 2> findBindingUV(const std::vector<MPoint> &controlPoints, const MPoint &queryPoint);

    /**
     * Retrieves the control points for a specific Bézier patch.
     * @param [in,out] matrixArray The array data handle containing the matrices of the patch.
     * @return A vector of MPoints representing the control points of the patch.
     */
    static std::vector<MPoint> getPatchPoints(MArrayDataHandle &matrixArray);
};
