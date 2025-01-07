#include "Collision2D.h"

#include <math.h>

int CollisionEllipse(Vector2* targetPos1, Vector2* targetPos2, Vector2 targetVec1, Vector2 targetVec2, float targetSpeed1, float targetSpeed2, float targetRadius1, float targetRadius2, int isRepulsion, int isTgt1Fix, int isTgt2Fix){
    
    // 円形の当たり判定
    if (sqrtf(powf(targetPos1->x - targetPos2->x, 2.0f) + powf(targetPos1->y - targetPos2->y, 2.0f)) <= targetRadius1 + targetRadius2) {

        // 斥力を持っていたら
        if (isRepulsion) {

            // ターゲット1が固定されている
            if (isTgt1Fix && !isTgt2Fix) {

                // x軸計算
                if (targetPos2->x - targetPos1->x > 0.0f) {

                    targetPos2->x = targetPos2->x + targetSpeed2 - targetVec2.x;

                } else {

                    targetPos2->x = targetPos2->x - targetSpeed2 - targetVec2.x;

                }

                // y軸計算
                if (targetPos2->y - targetPos1->y > 0.0f) {

                    targetPos2->y = targetPos2->y + targetSpeed2 - targetVec2.y;

                } else {

                    targetPos2->y = targetPos2->y - targetSpeed2 - targetVec2.y;

                }

            }
            // ターゲット2が固定されている
            if (!isTgt1Fix && isTgt2Fix) {

                // x軸計算
                if (targetPos1->x - targetPos2->x > 0.0f) {

                    targetPos1->x = targetPos1->x + targetSpeed1 - targetVec1.x;

                } else {

                    targetPos1->x = targetPos1->x - targetSpeed1 - targetVec1.x;

                }

                // y軸計算
                if (targetPos1->y - targetPos2->y > 0.0f) {

                    targetPos1->y = targetPos1->y + targetSpeed1 - targetVec1.y;

                } else {

                    targetPos1->y = targetPos1->y - targetSpeed1 - targetVec1.y;

                }

            }
            // どちらも固定されていない
            if (!isTgt1Fix && !isTgt2Fix) {

                targetPos2->x -= ((targetPos1->x - targetPos2->x) / 30.0f);
                targetPos2->y -= ((targetPos1->y - targetPos2->y) / 30.0f);

                targetPos1->x -= ((targetPos2->x - targetPos1->x) / 30.0f);
                targetPos1->y -= ((targetPos2->y - targetPos1->y) / 30.0f);

            }

        }

        // 当たっている
        return true;

    } else {

        // 当たっていない
        return false;

    }
    
}

int CollisionEllipseToRectangle(Vector2* targetPos1, Vector2* targetPos2, Vector2 targetVec1, Vector2 targetVec2, float targetSpeed1, float targetSpeed2, float targetRadius1, Vector2 targetsize2, int isRepulsion, int isTgt1Fix, int isTgt2Fix) {



    if (((targetPos1->x - targetRadius1 <= targetPos2->x + (targetsize2.x / 2.0f)) && (targetPos1->x + targetRadius1 >= targetPos2->x - (targetsize2.x / 2.0f))) &&
        ((targetPos1->y - targetRadius1 <= targetPos2->y + (targetsize2.y / 2.0f)) && (targetPos1->y + targetRadius1 >= targetPos2->y - (targetsize2.y / 2.0f)))) {

        if (isRepulsion) {

            // ターゲット1円が固定されている
            if (isTgt1Fix && !isTgt2Fix) {

                if (fabs(static_cast<double>(targetPos2->x - targetPos1->x)) > fabs(static_cast<double>(targetPos2->y - targetPos1->y))) {


                    // x軸計算
                    if (targetPos2->x - targetPos1->x > 0.0f) {

                        targetPos2->x = targetPos2->x + targetSpeed2 - targetVec2.x;

                    } else {

                        targetPos2->x = targetPos2->x - targetSpeed2 - targetVec2.x;

                    }

                } else {

                    // y軸計算
                    if (targetPos2->y - targetPos1->y > 0.0f) {

                        targetPos2->y = targetPos2->y + targetSpeed2 - targetVec2.y;

                    } else {

                        targetPos2->y = targetPos2->y - targetSpeed2 - targetVec2.y;

                    }
                }

            }
            // ターゲット2矩形が固定されている
            if (!isTgt1Fix && isTgt2Fix) {
                
                if (fabs(static_cast<double>(targetPos1->x - targetPos2->x)) > fabs(static_cast<double>(targetPos1->y - targetPos2->y))) {


                    // x軸計算
                    if (targetPos1->x - targetPos2->x > 0.0f) {

                        targetPos1->x = targetPos1->x + targetSpeed1 - targetVec1.x;

                    } else {

                        targetPos1->x = targetPos1->x - targetSpeed1 - targetVec1.x;

                    }

                } else {

                    // y軸計算
                    if (targetPos1->y - targetPos2->y > 0.0f) {

                        targetPos1->y = targetPos1->y + targetSpeed1 - targetVec1.y;

                    } else {

                        targetPos1->y = targetPos1->y - targetSpeed1 - targetVec1.y;

                    }
                }

            }
            // どちらも固定されていない
            if (!isTgt1Fix && !isTgt2Fix) {

                targetPos2->x -= ((targetPos1->x - targetPos2->x) / 30.0f);
                targetPos2->y -= ((targetPos1->y - targetPos2->y) / 30.0f);

                targetPos1->x -= ((targetPos2->x - targetPos1->x) / 30.0f);
                targetPos1->y -= ((targetPos2->y - targetPos1->y) / 30.0f);
            }
        }

        // 当たっている
        return true;

    } else {

        // 当たっていない
        return false;

    }
}

int CollisionRectangle(Vector2* aPos, Vector2 aSize, Vector2 bPos, Vector2 bSize,int isTransformX, int isTransformY) {
    
    Vector2 cAPos = *aPos;
    Vector2 cASize = aSize;
    Vector2 cBPos = bPos;
    Vector2 cBSize = bSize;

    Vector2 sizeDifference = {
        aSize.x / bSize.x,
        aSize.y / bSize.y
    };

    // Novice::ScreenPrintf(800, 0, "%.0f %.0f", sizeDifference.x, sizeDifference.y);

    int isHitX = false;
    int isHitY = false;
    
    // X軸の当たり判定
    if ((cAPos.x - (cASize.x * 0.5f)) < (cBPos.x + (cBSize.x * 0.5f)) &&
        (cAPos.x + (cASize.x * 0.5f)) > (cBPos.x - (cBSize.x * 0.5f))) {

        isHitX = true;
        // Novice::ScreenPrintf(500, 0, "isHitX");

    }

    // Y軸の当たり判定
    if ((cAPos.y - (cASize.y * 0.5f)) < (cBPos.y + (cBSize.y * 0.5f)) &&
        (cAPos.y + (cASize.y * 0.5f)) > (cBPos.y - (cBSize.y * 0.5f))) {

        isHitY = true;
        // Novice::ScreenPrintf(500, 20, "isHitY");
    }

    // 当たっているとき
    if (isHitX && isHitY) {

        // 横で当たっているか縦で当たっているか
        if (fabsf(cAPos.x - cBPos.x) / sizeDifference.x > fabsf(cAPos.y - cBPos.y) / sizeDifference.y) {
            
            // 右なら
            if (cAPos.x - cBPos.x > 0.0f) {

                cAPos.x -= (cAPos.x - (cASize.x * 0.5f)) - (cBPos.x + (cBSize.x * 0.5f));
            } else {

                cAPos.x -= (cAPos.x + (cASize.x * 0.5f)) - (cBPos.x - (cBSize.x * 0.5f));
            }

        } else {

            // 上なら
            if (cAPos.y - cBPos.y > 0.0f) {

                cAPos.y -= (cAPos.y - (cASize.y * 0.5f)) - (cBPos.y + (cBSize.y * 0.5f));

            } else {

                cAPos.y -= (cAPos.y + (cASize.y * 0.5f)) - (cBPos.y - (cBSize.y * 0.5f));
            }
        }
    }

    // 座標を返す
    if (isTransformX) {
        aPos->x = cAPos.x;
    }

    if (isTransformY) {
        aPos->y = cAPos.y;
    }

    // 返り値
    if (isHitX && isHitY) {
        return true;
    } else {
        return false;
    }
    
}

int CollisionPointToRectangle(Vector2* pointPos, Vector2 rectanglePos, Vector2 rectangleSize) {

    int hitX = false;
    int hitY = false;
    if (fabsf(pointPos->x - rectanglePos.x) <= rectangleSize.x * 0.5f) {
        hitX = true;
    }

    if (fabsf(pointPos->y - rectanglePos.y) <= rectangleSize.y * 0.5f) {
        hitY = true;
    }

    if (hitX && hitY) {

        if (fabsf(pointPos->x - rectanglePos.x) >= fabsf(pointPos->y - rectanglePos.y)) {

            if (pointPos->x <= rectanglePos.x) {
                pointPos->x += (-rectangleSize.x * 0.5f) - (pointPos->x - rectanglePos.x);
            } else {
                pointPos->x += (rectangleSize.x * 0.5f) - (pointPos->x - rectanglePos.x);
            }
            

        } else {

            if (pointPos->y <= rectanglePos.y) {
                pointPos->y += (-rectangleSize.y * 0.5f) - (pointPos->y - rectanglePos.y);
            } else {
                pointPos->y += (rectangleSize.y * 0.5f) - (pointPos->y - rectanglePos.y);
            }
            
        }

        return true;

    } else {

        return false;
    }
}

int IsHitRectangle(Vector2 aPos, Vector2 aSize, Vector2 bPos, Vector2 bSize) {

    Vector2 cAPos = aPos;
    Vector2 cASize = aSize;
    Vector2 cBPos = bPos;
    Vector2 cBSize = bSize;

    int isHitX = false;
    int isHitY = false;

    // X軸の当たり判定
    if ((cAPos.x - (cASize.x * 0.5f)) < (cBPos.x + (cBSize.x * 0.5f)) &&
        (cAPos.x + (cASize.x * 0.5f)) > (cBPos.x - (cBSize.x * 0.5f))) {

        isHitX = true;
        // Novice::ScreenPrintf(500, 0, "isHitX");

    }

    // Y軸の当たり判定
    if ((cAPos.y - (cASize.y * 0.5f)) < (cBPos.y + (cBSize.y * 0.5f)) &&
        (cAPos.y + (cASize.y * 0.5f)) > (cBPos.y - (cBSize.y * 0.5f))) {

        isHitY = true;
        // Novice::ScreenPrintf(500, 20, "isHitY");
    }

    // 返り値
    if (isHitX && isHitY) {
        return true;
    } else {
        return false;
    }
}

int IsHitCollisionEllipse(Vector2 targetPos1, Vector2 targetPos2, float targetRadius1, float targetRadius2) {
    // 円形の当たり判定
    if (sqrtf(powf(targetPos1.x - targetPos2.x, 2.0f) + powf(targetPos1.y - targetPos2.y, 2.0f)) <= targetRadius1 + targetRadius2) {
        return true;
    } else {
        return false;
    }
}

int IsHitCollisionEllipseToRectangle(Vector2 targetPos1, Vector2 targetPos2, float targetRadius1, Vector2 targetsize2) {

    if (((targetPos1.x - targetRadius1 <= targetPos2.x + (targetsize2.x / 2.0f)) && (targetPos1.x + targetRadius1 >= targetPos2.x - (targetsize2.x / 2.0f))) &&
        ((targetPos1.y - targetRadius1 <= targetPos2.y + (targetsize2.y / 2.0f)) && (targetPos1.y + targetRadius1 >= targetPos2.y - (targetsize2.y / 2.0f)))) {

        return true;
    } else {
        return false;
    }
    
}

//int IsHitCollisionMapChip(Vector2* targetPos, Vector2 targetSize, Vector2 mapChipSize, Mcp::AroundChipNum cn) {
//    
//    cn;
//}
