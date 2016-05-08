#ifndef __STATTRADEDATA_H__
#define __STATTRADEDATA_H__



class StatTradeData
{
public:
	double dBuyingAmount;
	double dBuyingCount;
	double dSellingAmount;
	double dSellingCount;
	double dAvePrice;
	double dMaxPrice;
	double dMinPrice;

	void Clear();
};



#endif // __STATTRADEDATA_H__
