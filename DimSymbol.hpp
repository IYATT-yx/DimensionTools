#pragma once

class DimSymbol
{
public:
	/**
	 * @brief ���òο��ߴ磬���С����
	 */
	static void cmdSetReferenceDimension();

	/**
	 * @brief ȡ���ο��ߴ磬�Ƴ�С����
	 */
	static void cmdCancelReferenceDimension();

	/**
	 * @brief ����ֱ���ߴ磬���ֱ������
	 */
	static void cmdSetDiameter();

	/**
	 * @brief ����Զ������
	 */
	static void cmdSetCustomSymbol();

	/**
	 * @brief ȡ���Զ������
	 */
	static void cmdCancelCustomSymbol();

private:
	// ����ص���������
	typedef void (*CallbackFun)(AcDbDimension*);

	/**
	 * @brief ���С����
	 * @param[in] pDim ������ı�ע����
	 */
	static void cbAddParentheses(AcDbDimension* pDim);

	/**
	 * @brief �Ƴ�С����
	 * @param[in] pDim ������ı�ע����
	 */
	static void cbRemoveParentheses(AcDbDimension* pDim);

	/**
	 * @brief ���ֱ������
	 * @param[in] pDim ������ı�ע����
	 */
	static void cbAddDiameter(AcDbDimension* pDim);

	/**
	 * @brief ѡ���ע�����ûص���������
	 * @param[in] callback ����ִ�д���Ļص�����
	 */
	static void selectAndProcess(CallbackFun callback);

	/**
	 * @brief �����׻���β����Զ������
	 * @param pDim ������ı�ע����
	 */
	static void cbAddCustomSymbol(AcDbDimension* pDim);

	/**
	 * @brief �����׻���β�Ƴ��Զ������
	 * @param pDim ������ı�ע����
	 */
	static void cbRemoveCustomSymbol(AcDbDimension* pDim);

	// ���ڱ�ʶ�������׻�����β
	static AcString beginningOrEnd;

	// ���ڴ洢�û������Ҫ��ӻ�ɾ���ķ���
	static AcString customSymbol;
};