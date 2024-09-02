#pragma once

class DimLock
{
public:
	/**
	 * @brief 【命令】固化标注
	 */
	static void cmdLockDim();

	/**
	 * @brief 【命令】重置标注
	 */
	static void cmdResetDim();

private:
	// 定义回调函数类型
	typedef void (*CallbackFun)(AcDbDimension*);

	/**
	 * @brief 精度舍入处理
	 * @param[out] sMeasureValue 处理后的结果以字符串形式返回
	 * @param[in] value 源数据值
	 * @param[in] precision 精度要求
	 * @param[in] isAugular 是否为角度数值【默认否】
	 */
	static void setPrecision(std::wstring& sMeasureValue, double& value, int& precision, bool isAugular = false);

	/**
	 * @brief 标注文本插值
	 * @param[in] sMeasureValue 尺寸值 
	 * @param[in,out] sText 标注文本
	 * @return true 未做处理【
	 */
	static bool insertValue(std::wstring& sMeasureValue, std::wstring& sText);

	/**
	 * @brief 【回调函数】将标注的尺寸转为文本
	 * @param[in,out] pDimension 要处理的标注对象
	 */
	static void cbDimNumToText(AcDbDimension* pDimension);

	/**
	 * @brief 【回调函数】清除标注文本
	 * @param[in,out] pDimension 要处理的标注对象
	 */
	static void cbResetDim(AcDbDimension* pDimension);

	/**
	 * @brief 遍历选择集筛选标注对象，并调用函数执行
	 * @param[in] pFun 【回调函数】用于处理标注对象的函数
	 */
	static void selectSetForeach(CallbackFun pFun);
};