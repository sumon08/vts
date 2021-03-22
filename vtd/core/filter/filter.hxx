#ifndef _FILTER_INCLUDE_H_
#define _FILTER_INCLUDE_H_

namespace vts
{
    class filter
    {
        float rc_short, rc_medium, rc_long;   
        float sampling_constant = 0.0005; 

        float GetBitaShort()
        {
            return (float)((96.0/(float)rc_short)*sampling_constant);
        }

        float GetBitaMedium()
        {
            return (float)((96.0/(float)rc_medium)*sampling_constant);
        }

        float GetBitaLong()
        {
            return (float)((96.0/(float)rc_long)*sampling_constant);
        }

        bool SetShortRC(float _rc)
        {
            rc_short = _rc;
            return true;
        }

        bool SetMediumRC(float _rc)
        {
            rc_medium = _rc;
            return true;
        }

        bool SetLongRC(float _rc)
        {
            rc_long = _rc;
            return true;
        }
        
        bool SetSamplingConstant (float _rc)
        {
            rc_long = _rc;
            return true;
        }

        public:
        filter(float _rc1,float _rc2,float _rc3, float _sc)
        {
            rc_short = _rc1;
            rc_medium = _rc2;
            rc_long = _rc3;
            sampling_constant = _sc;
        }
        float GetShortFiltered(float _value, float _adc_value)
        {
            return (float)(GetBitaShort() * _value + (1.0-GetBitaShort() * _adc_value));
        }

    };
}

#endif