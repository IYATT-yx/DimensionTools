#pragma once

class DimSymbol
{
public:
	/**
	 * @brief 设置参考尺寸，添加小括号
	 */
	static void cmdSetReferenceDimension();

	/**
	 * @brief 取消参考尺寸，移除小括号
	 */
	static void cmdCancelReferenceDimension();

	/**
	 * @brief 设置直径尺寸，添加直径符号
	 */
	static void cmdSetDiameter();

private:
	// 定义回调函数类型
	typedef void (*CallbackFun)(AcDbDimension*);

	/**
	 * @brief 添加小括号
	 * @param[in] pDim 待处理的标注对象
	 */
	static void cbAddParentheses(AcDbDimension* pDim);

	/**
	 * @brief 移除小括号
	 * @param[in] pDim 待处理的标注对象
	 */
	static void cbRemoveParentheses(AcDbDimension* pDim);

	/**
	 * @brief 添加直径符号
	 * @param[in] pDim 待处理的标注对象
	 */
	static void cbAddDiameter(AcDbDimension* pDim);

	/**
	 * @brief 选择标注并调用回调函数处理
	 * @param[in] callback 用于执行处理的回调函数
	 */
	static void selectAndProcess(CallbackFun callback);
};