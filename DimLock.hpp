#pragma once

class DimLock
{
public:
	/**
	 * @brief ������̻���ע
	 */
	static void cmdLockDim();

	/**
	 * @brief ��������ñ�ע
	 */
	static void cmdResetDim();

private:
	// ����ص���������
	typedef void (*CallbackFun)(AcDbDimension*);

	/**
	 * @brief �������봦��
	 * @param[out] sMeasureValue �����Ľ�����ַ�����ʽ����
	 * @param[in] value Դ����ֵ
	 * @param[in] precision ����Ҫ��
	 * @param[in] isAugular �Ƿ�Ϊ�Ƕ���ֵ��Ĭ�Ϸ�
	 */
	static void setPrecision(std::wstring& sMeasureValue, double& value, int& precision, bool isAugular = false);

	/**
	 * @brief ��ע�ı���ֵ
	 * @param[in] sMeasureValue �ߴ�ֵ 
	 * @param[in,out] sText ��ע�ı�
	 * @return true δ������
	 */
	static bool insertValue(std::wstring& sMeasureValue, std::wstring& sText);

	/**
	 * @brief ���ص�����������ע�ĳߴ�תΪ�ı�
	 * @param[in,out] pDimension Ҫ����ı�ע����
	 */
	static void cbDimNumToText(AcDbDimension* pDimension);

	/**
	 * @brief ���ص������������ע�ı�
	 * @param[in,out] pDimension Ҫ����ı�ע����
	 */
	static void cbResetDim(AcDbDimension* pDimension);

	/**
	 * @brief ����ѡ��ɸѡ��ע���󣬲����ú���ִ��
	 * @param[in] pFun ���ص����������ڴ����ע����ĺ���
	 */
	static void selectSetForeach(CallbackFun pFun);
};