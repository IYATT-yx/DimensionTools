#pragma once

class DimSymbol
{
public:
	/**
	 * @brief ���òο��ߴ磬����С����
	 */
	static void cmdSetReferenceDimension();

	/**
	 * @brief ȡ���ο��ߴ磬�Ƴ�С����
	 */
	static void cmdCancelReferenceDimension();

private:
	// ����ص���������
	typedef void (*CallbackFun)(AcDbDimension*);

	/**
	 * @brief ����С����
	 * @param[in] pDim �������ı�ע����
	 */
	static void cbAddParentheses(AcDbDimension* pDim);

	/**
	 * @brief �Ƴ�С����
	 * @param[in] pDim �������ı�ע����
	 */
	static void cbRemoveParentheses(AcDbDimension* pDim);

	/**
	 * @brief ѡ���ע�����ûص���������
	 * @param[in] callback ����ִ�д����Ļص�����
	 */
	static void selectAndProcess(CallbackFun callback);
};