 /*****************************************************************************
*  3DCamera SDK header
*
*
*  @file     Types.hpp
*  @brief    3DCamera sdk header
*
*  @version  1.0
*  @date     2019 / 08 / 17
*
*****************************************************************************/
#ifndef __TYPES_HPP__
#define __TYPES_HPP__

#ifdef __cplusplus
extern "C" {
#endif

	typedef struct CS_SDK_VERSION_TAG
	{			
		const char*	version;		//�汾��
		const char*	name;			//ģ������
		const char*	author;			//������
		const char*	date;			//��������
		const char*	desc;			//������ÿ���޸Ķ���Ҫ����
	}CS_SDK_VERSION, PCS_SDK_VERSION;

	//ProbeType
	typedef enum
	{
		PT_START,
		PT_STOP
	}ProbeType;

	/**
	 * @~chinese
	 * @brief	IMU�궨ƽ��
	 * @~english
	 * @brief	IMU CalibrationPlane
	 */
	typedef enum {
		IMU_XY,			//XYƽ��
		IMU_XZ,			//XZƽ��
		IMU_YZ,			//YZƽ��
	}IMU_CALIBRATTION_PLANE;

	/**
	 * @~chinese
	 * @brief	IMU�궨״̬
	 * @~english
	 * @brief	IMU Calibration state
	 */
	typedef enum {
		CALIBRATION_STATE_ING,			//δ���
		CALIBRATION_STATE_FIN			//�����
	}IMU_CALIBRATTION_STATE;

	//CameraType
	typedef enum
	{
		CAMERA_UNKNOW,				//unknow camera type
		CAMERA_HD,					//HD
		CAMERA_SURFACE,				//surface
		CAMERA_SENSE_PRO,			//sense pro
		CAMERA_POP_1,			    //pop1
		CAMERA_POP_2 = 10,		    //pop2
		CAMERA_MINI_NO_RGB,			//mini camera without rgb sensor
		CAMERA_MINI_NORMAL,			//
        CAMERA_TRACER_P1,           //tracer p1
		CAMERA_RANGE,				//Range
		CAMERA_TRACER_P2,           //tracer p2
		CAMERA_POP_3,               //pop3
	}CameraType;

#define FRAMERATE_ANY 0
#define CAMERA_SERIAL_MAX		32
#define FIRMWARE_VERSION_MAX	32
#define ALGORITHM_VERSION_MAX	32

#ifndef OUT
#define OUT
#endif

#ifndef IN
#define IN
#endif

typedef enum CAMERA_STATUS
{
	CS_NONE,			/**< @~chinese ��Ч�����             @~english invalid camera*/
	CS_IDLE,			/**< @~chinese ������             @~english in idle status*/
	CS_CONNECTED_BY_SDK,		/**< @~chinese ��SDK������             @~english current sdk connect to the camera.*/
	CS_CONNECTED_BY_OTHER,		/**< @~chinese ����ʵ��(����)������             @~english other instance connect to the camera*/
}CAMERA_STATUS;

/** 
* @~chinese
* ö��: ���صĴ�����
* @~english
* enumeration: returned error code
**/
typedef enum ERROR_CODE
{
	SUCCESS = 0,					/**< @~chinese �ɹ�             @~english success*/ 
	ERROR_PARAM,					/**< @~chinese �����������     @~english param input error*/
	ERROR_DEVICE_NOT_FOUND,			/**< @~chinese δ�ҵ��豸       @~english device not found*/
	ERROR_DEVICE_NOT_CONNECT,		/**< @~chinese �豸δ����       @~english device not connected*/
	ERROR_DEVICE_BUSY,				/**< @~chinese �豸æ           @~english device busy*/
	ERROR_STREAM_NOT_START = 5,			/**< @~chinese ����δ��       @~english stream not start*/
	ERROR_STREAM_BUSY,				/**< @~chinese ���Ѵ�         @~english stream had started*/
	ERROR_FRAME_TIMEOUT,			/**< @~chinese ��ȡ֡����ʧ��   @~english get frame failed*/
	ERROR_NOT_SUPPORT,				/**< @~chinese �в�֧��         @~english not support*/
	ERROR_PROPERTY_GET_FAILED,		/**< @~chinese ��ȡ����ʧ��     @~english get property failed*/
	ERROR_PROPERTY_SET_FAILED=10,		/**< @~chinese ��������ʧ��     @~english set property failed*/
	ERROR_HID_CHANNEL_ERROR,		/**< @~chinese hid ͨ���쳣	     @~english hid channel error*/
	ERROR_HID_WRITE_ERROR,
	ERROR_HID_READ_ERROR,
	ERROR_UNKNOW
}ERROR_CODE;

/**
* @~chinese
* ö��: ���������
* @~english
* enumeration: stream type
**/
typedef enum STREAM_TYPE
{
	STREAM_TYPE_DEPTH	= 0, /**<@~chinese �����  @~english Depth camera stream */
    STREAM_TYPE_RGB		= 1, /**<@~chinese RGB��   @~english RGB camera stream */
	STREAM_TYPE_COUNT
}STREAM_TYPE;


/// \~chinese
/// \defgroup StreamFormat ��������ʽ
/// \brief �������RGB����֧�ֵ����и�ʽ
/// @{
/// \~english
/// \defgroup StreamFormat Stream format
/// \brief Format of depth stream and RGB stream
/// @{
/**
* @~chinese
* ö��: �����ݸ�ʽ
* @~english
* enumeration: stream format
**/
typedef enum STREAM_FORMAT
{
	STREAM_FORMAT_MJPG		= 0x00,		 /**< @~chinese RGB����MJPGѹ��������			
											  @~english MJPG compressed data*/ 
	STREAM_FORMAT_RGB8		= 0x01,		 /**< @~chinese RGB����8λ��,��,��3ͨ������			
											  @~english 8-bit red, green and blue channels*/ 
	STREAM_FORMAT_Z16		= 0x02,		 /**< @~chinese ����������ͼ��ʽ, ÿһ�����ֵ��unsigned short��ʾ
											  @~english 16-bit unsigned short depth values. The depth in millimeters is equal to depth scale * pixel value. */ 
	STREAM_FORMAT_Z16Y8Y8	= 0x03,		 /**< @~chinese ����������ͼ+����ͼ��ϸ�ʽ,	
														ͨ��FRAME_DATA_FORMAT_Z16���������ݣ�
														ͨ��FRAME_DATA_FORMAT_IR_LEFT��������ͼ, 
														ͨ��FRAME_DATA_FORMAT_IR_RIGHT����Һ���ͼ
											  @~english output depth map and infrared, 
														get depth map by FRAME_DATA_FORMAT_Z16
														get left infrared by FRAME_DATA_FORMAT_IR_LEFT,
														get right infrared by FRAME_DATA_FORMAT_IR_RIGHT*/ 
	STREAM_FORMAT_PAIR		= 0x04,		 /**< @~chinese ������ĺ���ͼ��ʽ��������˫Ŀ���
														ͨ��FRAME_DATA_FORMAT_IR_LEFT��������ͼ, 
														ͨ��FRAME_DATA_FORMAT_IR_RIGHT����Һ���ͼ	
											  @~english output infrared��suitable for binocular camera
														get left infrared by FRAME_DATA_FORMAT_IR_LEFT,
														get right infrared by FRAME_DATA_FORMAT_IR_RIGHT*/ 
	STREAM_FORMAT_H264		= 0x05,		 /**< @~chinese RGB����H264ѹ��������			
											  @~english H264 compressed data*/ 
	STREAM_FORMAT_I8DS      = 0x100,	 /**< @~chinese ����������Ԥ����ʽ
														ͨ��FRAME_DATA_FORMAT_IR_LEFT��������ͼ,
														ͨ��FRAME_DATA_FORMAT_IR_RIGHT����Һ���ͼ��
														ͨ��FRAME_DATA_FORMAT_VCENTER_LEFT��������ͼ�й⵶���ĵ�y��������,
														ͨ��FRAME_DATA_FORMAT_VCENTER_RIGHT����Һ���ͼ�й⵶���ĵ�y�������飬
														ͨ��FRAME_DATA_FORMAT_LASER_WIDTH_LEFT ��������ͼ�⵶�������,
														ͨ��FRAME_DATA_FORMAT_LASER_WIDTH_RIGHT����Һ���ͼ�⵶�������
									    	  @~english output down sampled infrared for preview
														get left infrared by FRAME_DATA_FORMAT_IR_LEFT, 
														get right infrared by FRAME_DATA_FORMAT_IR_RIGHT,
														get left laser center by FRAME_DATA_FORMAT_VCENTER_LEFT,
														get right laser center by FRAME_DATA_FORMAT_VCENTER_RIGHT,
														get left laser width by FRAME_DATA_FORMAT_LASER_WIDTH_LEFT,
														get right laser width by FRAME_DATA_FORMAT_LASER_WIDTH_RIGHT*/
	STREAM_FORMAT_XZ32		= 0x101,	 /**< @~chinese ���������ʽ, ͨ��cs::Pointcloud::generatePointsFromXZ����ɵ���		
											  @~english output point cloud, call cs::Pointcloud::generatePointsFromXZ to compute a point cloud*/
	STREAM_FORMAT_GRAY		= 0x102,	 /**< @~chinese ������ĺ���ͼ��ʽ�������ڵ�Ŀ���
											  @~english output infrared��suitable for monocular cameras */ 
	STREAM_FORMAT_COUNT
}STREAM_FORMAT;

/**
* @~chinese
* ö��: ֡���ݸ�ʽ�����ڻ�ȡ�����������е�ָ����ʽ������ʼ��ַ
* @~english
* enumeration: format of frame data, used for get specified data in a composite frame
**/
typedef enum FRAME_DATA_FORMAT
{
	FRAME_DATA_FORMAT_Z16				= 0x00,		/**< @~chinese ����������ͼ��ʽ, ÿһ�����ֵ��unsigned short��ʾ
														 @~english 16-bit unsigned short depth values. The depth in millimeters is equal to depth scale * pixel value. */ 
	FRAME_DATA_FORMAT_IR_LEFT			= 0x01,		/**< @~chinese �����ͼ���ݣ� 8-bit unsigned char��ʾһ���Ҷ�ֵ				
														 @~english 8-bit unsigned char gray level of left infrared*/
	FRAME_DATA_FORMAT_IR_RIGHT			= 0x02,		/**< @~chinese �Һ���ͼ���ݣ� unsigned char��ʾһ���Ҷ�ֵ				
														 @~english 8-bit unsigned char gray level of right infrared*/
	FRAME_DATA_FORMAT_VCENTER_LEFT		= 0x03,		/**< @~chinese �����ͼ�⵶���ģ� unsigned char��ʾһ��y����				
														 @~english 8-bit unsigned char y coordinate of left laser center*/
	FRAME_DATA_FORMAT_VCENTER_RIGHT		= 0x04,		/**< @~chinese �Һ���ͼ�⵶���ģ� unsigned char��ʾһ��y����				
														 @~english 8-bit unsigned char y coordinate of right laser center*/
	FRAME_DATA_FORMAT_LASER_WIDTH_LEFT	= 0x05,		/**< @~chinese �����ͼ�⵶��ȣ� unsigned char��ʾһ�����ֵ, �⵶̫��ʱӰ���ľ�ȷ��				
														 @~english 8-bit unsigned char left laser width array��The accuracy of the point is affected when the laser is too wide*/
	FRAME_DATA_FORMAT_LASER_WIDTH_RIGHT = 0x06,		/**< @~chinese �Һ���ͼ�⵶��ȣ� unsigned char��ʾһ�����ֵ, �⵶̫��ʱӰ���ľ�ȷ��					
														 @~english 8-bit unsigned char right laser width array��The accuracy of the point is affected when the laser is too wide*/
}FRAME_DATA_FORMAT;
/// @}


/// \~chinese
/// \defgroup PropertyType ��������
/// \brief �о����п����õĻ�������
/// @{
/// \~english
/// \defgroup PropertyType Basic property
/// \brief List basic properties
/// @{

/**
* @~chinese
* ö��: ����Ļ�������
* @~english
* enumeration: basic property of camera
**/
typedef enum PROPERTY_TYPE
{
    PROPERTY_GAIN                       = 0x00,	/**<@~chinese ����
                                                              �����������,����������������,������Ⱦ����½������ڷ�Χ1~16, �߾���ʱ,���������3
                                                    @~english gain of depth camera or RGB camera*/
    PROPERTY_EXPOSURE                   = 0x01,	/**<@~chinese �ع�ֵ
                                                              ���ڵ����������,��ֵԽ������Խ��,������������,����֡�ʻ������ع�ʱ�����������,���ڷ�Χ3000~60000΢��
                                                    @~english Controls exposure time of depth camera or RGB camera*/
	PROPERTY_FRAMETIME					= 0x02,	/**<@~chinese ֡ʱ��            @~english Frame time of depth camera */
	PROPERTY_FOCUS						= 0x03,	/**<@~chinese ����              @~english Focus of RGB camera*/
	PROPERTY_ENABLE_AUTO_FOCUS			= 0x04,	/**<@~chinese �Ƿ��Զ��Խ�      @~english Enable / disable auto-focus of RGB camera*/
	PROPERTY_ENABLE_AUTO_EXPOSURE		= 0x05, /**<@~chinese �Ƿ��Զ��ع�      @~english Enable / disable auto-exposure of RGB camera*/
	PROPERTY_ENABLE_AUTO_WHITEBALANCE	= 0x06, /**<@~chinese �Ƿ��Զ���ƽ��    @~english White balance of RGB camera*/
	PROPERTY_WHITEBALANCE				= 0x07,	/**<@~chinese ��ƽ��ֵ          @~english adjust white balance of RGB camera*/
	PROPERTY_WHITEBALANCE_R				= 0x08,	/**<@~chinese ��ƽ��Rͨ��       @~english Channel r of RGB camera, adjust white balance*/
	PROPERTY_WHITEBALANCE_B				= 0x09,	/**<@~chinese ��ƽ��Bͨ��       @~english Channel b of RGB camera, adjust white balance*/
	PROPERTY_WHITEBALANCE_G				= 0x10,	/**<@~chinese ��ƽ��Gͨ��       @~english Channel g of RGB camera, adjust white balance*/
	
} PROPERTY_TYPE;
/// @}

/**
* @~chinese
* ö��: �������ģʽ 
* @~english
* enumeration: trigger mode
**/
typedef enum TRIGGER_MODE
{
	TRIGGER_MODE_OFF		= 0, /**< @~chinese �رմ���ģʽ��������������	
									  @~english output depth map continuously*/ 
	TRIGGER_MODE_HARDWAER	= 1, /**< @~chinese �ⴥ��ģʽ����Ҫ�ڴ���������Ӳ���źŲ��ܳ�ͼ
									  @~english external trigger mode,you should input hardware pulse to get depth frame*/
	TRIGGER_MODE_SOFTWAER	= 2, /**< @~chinese ����ģʽ����Ҫ����cs::ICamera::softTrigger���ܳ����ͼ
									  @~english software trigger mode,you should call cs::ICamera::softTrigger to get depth frame*/
}TRIGGER_MODE;

/**
* @~chinese
* ö��: �߶�̬��ģʽ
* @~english
* enumeration: mode of HDR
**/
typedef enum HDR_MODE
{
	HDR_MODE_OFF			= 0,	/**< @~chinese �ر�				
                                         @~english HDR off*/ 
	HDR_MODE_HIGH_RELECT	= 1,	/**< @~chinese �߷�ģʽ�����ڲ�߷�����,	
                                                   �ᰴ���趨���ع⼶��,���ӽϵ͵��ع�������ж���ع������ں�������ع⼶�����û��趨
                                         @~english suitable for shiny object*/
	HDR_MODE_LOW_RELECT		= 2,	/**< @~chinese ��ɫģʽ�����ڲ���ɫ����,	
                                                   �ᰴ���趨���ع⼶��,���ӽϸ��ع�������м����ع������ں�������ع⼶�����û��趨
                                         @~english suitable for dark object*/
	HDR_MODE_ALL_RELECT		= 3		/**< @~chinese ����ģʽ�����ڲ⸴�ϱ���	
                                                   ��ƽ�������ع⼶��,�ֱ����ӽϵ��ع�����ͽϸ��ع���������ж���عⲢ�ں�������ع⼶�����û��趨
                                         @~english suitable for composite object*/
}HDR_MODE;

/**
* @~chinese
* @brief ö��: �Զ��ع�ģʽ
* @~english
* @brief enumeration: mode of auto exposure
**/
typedef enum AUTO_EXPOSURE_MODE
{
	AUTO_EXPOSURE_MODE_CLOSE = 0,			/**< @~chinese �ر�				
                                                 @~english off*/
	AUTO_EXPOSURE_MODE_FIX_FRAMETIME = 1,	/**< @~chinese �̶�֡��ģʽ���ڵ�ǰ֡������Χ���Զ�ʵʱ����������ع�ʱ�������, ��������������֡��
											     @~english adjust exposure automatically and keep frame time unchanged*/
	AUTO_EXPOSURE_MODE_HIGH_QUALITY = 2,	/**< @~chinese ������ģʽ���Ի���������ģ��ΪĿ��, �Զ�ʵʱ����������ع�ʱ�������, ͬʱ�ᰴ�����֡��
											     @~english adjust exposure and frame time automatically*/
    AUTO_EXPOSURE_MODE_FORE_GROUND = 3		/**< @~chinese ��������ģʽ���Ի���������ģ��ΪĿ��, �Զ�ʵʱ����������ع�ʱ�������, ͬʱ�ᰴ�����֡��
                                                 @~english adjust exposure and frame time automatically*/
}AUTO_EXPOSURE_MODE;

/**
* @~chinese
* @brief ö��: ���紫��ѹ����ʽ
* @~english
* @brief enumeration: mode of compress
**/
typedef enum NETWORK_COMPRESS_MODE
{
	NETWORK_COMPRESS_MODE_CLOSE = 0,		/**< @~chinese �ر�               @~english off*/
	NETWORK_COMPRESS_MODE_ZIP	= 1,		/**< @~chinese ZIP(Ĭ������)      @~english ZIP(Default)*/
}NETWORK_COMPRESS_MODE;


/**
* @~chinese
* @brief ������ȷ�Χ��������Χ��ֵ��������
* @~english
* @brief range of depth, value out of range will be set to zero
**/
typedef struct DepthRange
{
	int min;		/**< @~chinese �����Сֵ        @~english minimum of depth*/ 
	int max;		/**< @~chinese ������ֵ        @~english maximum of depth*/ 
}DepthRange;

/**
* @~chinese
* @brief ��������ʱ�豸��IP���ã���autoEnable����Ϊtrueʱ����������ipFourthByte
* @~english
* @brief IP setting, when autoEnable is true, there is no need to set ipFourthByte
**/
typedef struct IpSetting
{
	unsigned int autoEnable;	/**< @~chinese �Ƿ���DHCP             @~english enable/disable DHCP*/ 
	unsigned char ipFourthByte;	/**< @~chinese IP��ַ�ĵ���λ           @~english the fourth byte of ip*/ 
}IpSetting;

typedef struct CameraIpSetting
{
    unsigned char autoEnable;	/**< @~chinese �Ƿ���DHCP             @~english enable/disable DHCP*/
    unsigned char ipBytes[4];	/**< @~chinese IP��ַ {192,168,3,99}    @~english the first byte of ip*/
}CameraIpSetting;

/**
 * @~chinese
 * @brief	����ģʽ
 * @~english
 * @brief	net working mode
 */
typedef enum {
	NET_WORKING_TERMINAL,			//�ն�ģʽ
	NET_WORKING_WIFI_HOST_AP,		//5G AP ģʽ��Ĭ����5Gģʽ
	NET_WORKING_WIFI_HOST_2_4G,		//2.4G APģʽ��2.4Gģʽ�����ţ����ڲ�ʹ��
	NET_WORKING_TERMINAL_ONLY,		//�ն�ģʽ���ر�AP
	NET_WORKING_WIFI_HOST_5GONLY,	//APģʽ���ر��ն�
}NET_WORKING_MODE;

#pragma pack(push, 4)
typedef enum WifiChannel
{
	WIFI_CHANNEL_DEFAULT = 0,	//Ĭ���ŵ����ڲ�ת��ΪWIFI_CHANNEL_44
	WIFI_CHANNEL_44 = 44,
	WIFI_CHANNEL_149 = 149
}WifiChannel;

/**
 * @~chinese
 * @brief		����������Ϣ,��Ӧ����PROPERTY_EXT_NET_WORKING_INFO
 * @~english
 * @brief		net working info,corresponding PROPERTY_EXT_NET_WORKING_INFO
 */
typedef struct
{
	NET_WORKING_MODE	netMode;
	unsigned char		cEnable;		//0:disable,1:enable
	char 				reserved[3];	//reserved
	char 				ssid[100];		//ap name or wifi host name
	char 				psk[100];		//password 
	WifiChannel			channel;		//WIFIͨ��
}NetworkingInfo;

#pragma pack(pop)

/**
* @~chinese
* @brief HDR�Զ�ģʽʱ�ع⼶���������ع�֮��ı�������
* @~english
* @brief exposure times and interstage scale of HDR
**/
typedef struct HdrScaleSetting
{
	unsigned int highReflectModeCount;	/**< @~chinese �߷�ģʽ�ع⼶��         @~english exposure times of high-reflective mode*/ 
	unsigned int highReflectModeScale;	/**< @~chinese �߷�ģʽ�����䱶��       @~english interstage scale of high-reflective mode*/ 
	unsigned int lowReflectModeCount;	/**< @~chinese ��ɫģʽ�ع⼶��         @~english exposure times of low-reflective mode*/ 
	unsigned int lowReflectModeScale;	/**< @~chinese ��ɫģʽ�����䱶��       @~english interstage scale of low-reflective mode*/ 
}HdrScaleSetting;

#pragma pack(push, 1)

/**
* @~chinese
* @brief HDRĳһ���ع�Ĳ���
* @~english
* @brief exposure param of HDR
**/
typedef struct HdrExposureParam
{
	unsigned int  exposure;	/**< @~chinese �ع�ʱ��         @~english exposure time*/ 
	unsigned char gain;		/**< @~chinese ����             @~english gain*/ 
}HdrExposureParam;

/**
* @~chinese
* @brief HDR�ع����
* @~english
* @brief all exposure params of HDR
**/
typedef struct HdrExposureSetting
{
	unsigned char count;			/**< @~chinese ���ع⼶��        @~english total exposure times of HDR*/ 
	HdrExposureParam param[11];		/**< @~chinese �����ع����      @~english all params of HDR*/ 
}HdrExposureSetting;

/**
* @~chinese
* @brief HDRĳһ�����ع�ʱ�估�����������
* @~english
* @brief exposure and laser level of HDR
**/
typedef struct HdrBrightnessParam
{
	unsigned char laserLevel;		/**< @~chinese �������ȼ�        @~english brightness of laser*/ 
	float exposure;					/**< @~chinese �ع�ʱ��          @~english exposure time*/ 
}HdrBrightnessParam;

/**
* @~chinese
* @brief HDR���м�����ع�ʱ�估�����������
* @~english
* @brief all settings of exposure and laser level
**/
typedef struct HdrBrightnessSetting
{
	unsigned char count;			/**< @~chinese ���ع⼶��        @~english total exposure times of HDR*/
	HdrBrightnessParam param[11];	/**< @~chinese �����ع����      @~english all params of HDR*/
}HdrBrightnessSetting;

typedef struct DepthRgbMatchParam
{
	int		iRgbOffset;				/**< @~chinese ƥ��ʱRGBʱ�����ƫ��ֵ     @~english the offset of rgb frame's timestamp when matching*/
	int		iDifThreshold;			/**< @~chinese �����rgbʱ����������ֵ   @~english the threshold of depth and rgb frame's timestamp*/
	bool	bMakeSureRgbIsAfterDepth;	/**< @~chinese ȷ��RGBʱ�����depth֮��   @~english make sure rgb's timestamp is after depth.*/
}DepthRgbMatchParam;

//����pattern�л�ǰ����Ҫstop_stream[0x483]��start_stream[0x481],sdk���Ѿ�������ˣ��ⲿ����Ҫ�ظ�����483��481
//POP2���㷨��1��3�л�������־��ģʽʱʹ��1��������ģʽʱʹ��3--����
//EN_FRINGE_PATTERN_TYPE_3FREQ4STEP_MULTI��18֡��֡��
const int id_msg_set_fringe_pattern_t = 0xa05;
typedef enum EN_FRINGE_PATTERN_TYPE_T 
{
	EN_FRINGE_PATTERN_TYPE_STANDARD = 0x00,
	EN_FRINGE_PATTERN_TYPE_STANDARD_WHITE_ADDED = 0x01,
	EN_FRINGE_PATTERN_TYPE_MULTI_DEPTH = 0x02,
	EN_FRINGE_PATTERN_TYPE_MULTI_DEPTH_WHITE_ADDED = 0x03,
	EN_FRINGE_PATTERN_TYPE_MULTI_DEPTH_DOUBLE_WHITE_ADDED = 0x04,
	EN_FRINGE_PATTERN_TYPE_3FREQ4STEP = 0x05,
	EN_FRINGE_PATTERN_TYPE_3FREQ4STEP_MULTI_DEPTH = 0x06,

}FRINGE_PATTERN_TYPE;

typedef struct MaxFrameTimeGain_tag
{
	int		iMaxFrame;	//the recommended value is 15000
	int		iMaxGain;	//the recommended value is 48
}MaxFrameTimeGain;

typedef struct StreamResolution_tag
{
	int iWidth;
	int iHeight;
}StreamResolution;

typedef struct DepthRoi_tag
{
	int left;		//[0,100],coordinates take the value 0-100,which represents the percentage of width or height.
	int top;		//[0,100]
	int right;		//[0,100]
	int bottom;		//[0,100]
}DepthRoi;

typedef struct HidHeader_tag
{
	int		magic;
	int		type;
	char	checksum[32]; // 0 not check, other check
	int		iDataLen;//ָʾacData�е���Ч���ݴ�С
}HidHeader;

typedef struct WriteReadHidData_tag
{
	int iDataMax;		//ָʾacData�����ÿռ�
	int iTimeoutMs;		//ָʾ��ȡ���ݵĳ�ʱʱ�䣬��λ����

	unsigned char	reportId;//�ر�+1(ReportId)
	HidHeader		hidHeader;
	char	acData[1];		//ָʾ��������

}WriteReadHidData;

//͸�ӱ任��������,����
#define PER_TRANSF_MATRIX_ROW	4
#define PER_TRANSF_MATRIX_COL	4
#define PER_TRANSF_MATRIX_SIZE	16

/**
* @~chinese
* @brief ͸�ӱ任����
* @~english
* @brief Perspective transformation matrix
**/
typedef struct PerspectiveTransformationMatrix 
{
	short width;
	short height;
	union 
	{
		float matrix[PER_TRANSF_MATRIX_ROW][PER_TRANSF_MATRIX_COL];
		float mat_[PER_TRANSF_MATRIX_SIZE];
	};
	
} PerspectiveTransformationMatrix;

/**
* @~chinese
* @brief ֵ��Χ
* @~english
* @brief Value range
**/
typedef struct ValueRange {
	float fMin_;
	float fMax_;
	float fStep_;
}*ValueRange_PTR;

#pragma pack(pop)




/// \~chinese
/// \defgroup PropertyExtensionType ��չ����
/// \brief �о����п����õ���չ����
/// @{
/// \~english
/// \defgroup PropertyExtensionType Extensional property
/// \brief List extensional properties
/// @{

/**
* @~chinese
* @brief ö��: ��չ����
* @~english
* @brief enumeration: extensional of property
**/
typedef enum PROPERTY_TYPE_EXTENSION
{
	PROPERTY_EXT_DEPTH_SCALE			= 0x0,	 /**< @~chinese ���ֵ����ϵ��                @~english depth unit for real distance */
	PROPERTY_EXT_TRIGGER_MODE			= 0x1,	 /**< @~chinese ����ģʽ                      @~english/PROPERTY_EXT_TRIGGER_OUT_MODE set trigger mode ,normal or trigge mode, value 1 stands for software trigger mode, value 2 stands for hardware trigger mode, other stands for trigger off(default)*/
	PROPERTY_EXT_TRIGGER_OUT_MODE		= 0x2,	 /**< @~chinese �Ƿ����������              @~english enable/disable trigger out*/
	PROPERTY_EXT_HDR_BRIGHTNESS			= 0x3,	 /**< @~chinese HDR��������                   @~english all params of HDR*/
	PROPERTY_EXT_IP_SETTING				= 0x4,	 /**< @~chinese deprecated IP����             @~english IP setting*/
	PROPERTY_EXT_NETWORK_COMPRESS		= 0x5,	 /**< @~chinese ���紫��ʱ���Ƿ�ѹ��
													  @~english whether the stream compresses when transmited by network*/
    PROPERTY_EXT_SERIAL_NUMBER          = 0x6,   /**< @~chinese �޸����к�*/
    PROPERTY_EXT_MAC_ADDRESS            = 0x7,   /**< @~chinese �޸�mac��ַ*/
    PROPERTY_EXT_CAMERA_IP              = 0x8,	 /**< @~chinese IP����                        @~english IP setting*/
	PROPERTY_EXT_AP_NET_WORKING_INFO	= 0x9,   /**<@~chinese apģʽ���� ����,�ο�NetworkingInfo	  @~english property of net working,reference NetworkingInfo*/
	PROPERTY_EXT_FAST_SCAN_MODE			= 0x0A,   /**<@~chinese  ����ɨ��ģʽ,�ο�bFastScanMode	  @~english property of fast scan mode ,reference bFastScanMode*/
	PROPERTY_EXT_HARDSYNCSWITCH			= 0x0B,		/**<@~chinese  Ӳͬ������,�ο�bHardSyncSwitch	  @~english property of hard synchronization ,reference bHardSyncSwitch*/
	PROPERTY_EXT_DEPTH_RGB_MATCH_PARAM	= 0x0C,		/**<@~chinese  ��Ⱥ�RGB֡ƥ�����,�ο�DepthRgbMatchParam	  @~english property of depth and rgb match param ,reference DepthRgbMatchParam*/
	PROPERTY_EXT_PAUSE_DEPTH_STREAM		= 0x0D,		/**<@~chinese  ��ͣ�����	  @~english pause the depth stream*/
	PROPERTY_EXT_RESUME_DEPTH_STREAM	= 0x0E,		/**<@~chinese  �ָ������	  @~english resume the depth stream*/
	PROPERTY_EXT_TERMINAL_NET_WORKING_INFO = 0x10,   /**<@~chinese �ն�ģʽ���� ����,�ο�NetworkingInfo	  @~english property of net working,reference NetworkingInfo*/
	PROPERTY_EXT_IS_WIFI_HOST_MODE		= 0x11,   /**<@~chinese �ж��Ƿ���wifi-hostģʽ ����,bIsWifiHostMode	  @~english property of bool ,which is in wifi host mode,reference bIsWifiHostMode*/
	PROPERTY_EXT_CLEAR_FRAME_BUFFER		= 0x13,   /**<@~chinese ���SDK�ڲ���Frame����	  @~english empty sdk frame buffer*/
	PROPERTY_EXT_GET_RECONSTRUCTIONMAT	= 0x14,	 /**<@~chinese ��ȡ�Ӳ��ؽ����Ƶľ���	  @~english get parallax reconstruction point cloud.*/

	PROPERTY_EXT_EXPOSURE_TIME_RGB      = 0x15,	 /**<@~chinese �ع�ʱ��,��λ΢��,����RGB��	  @~english exposure time,unit us.*/
	PROPERTY_EXT_EXPOSURE_TIME_RANGE_RGB = 0x16, /**<@~chinese �ع�ʱ�䷶Χ,��λ΢��,����RGB��	  @~english exposure time,unit us.*/
	PROPERTY_EXT_CPU_TEMPRATRUE			= 0x17,  /**<@~chinese CPU�¶�,��λ���϶�,	  @~english CPU tempratrue,unit degree Celsius */
	//PROPERTY_EXT_GET_CAMERA_STATE       = 0x18, /**< @~chinese ��ȡ�����ǰ״̬,	  @~english Get camera current state */
	PROPERTY_EXT_IS_SUPPORT_GYRO        = 0x19,   /**< @~chinese �ж�����Ƿ�֧��������, �ο�bSupportGyro	  @~english the camera supports gyroscope or not, reference bSupportGyro*/
	PROPERTY_EXT_GET_GYRO_VERSION       = 0x20,   /**< @~chinese ��ȡ��������ǰ汾��Ϣ, �ο�gyroVersion	  @~english get camera gyroscope version information,reference gyroVersion */
 
	PROPERTY_EXT_SET_FAKE_MODE			= 0x904, /**< @~chinese ������ٷֱ���                @~english set fake mode */
	PROPERTY_EXT_AUTO_EXPOSURE_MODE		= 0x912, /**< @~chinese �������Զ��ع�ģʽ,�ο�AUTO_EXPOSURE_MODE         @~english auto exposure mode of depth camera��reference AUTO_EXPOSURE_MODE*/
	PROPERTY_EXT_DEPTH_ROI				= 0x913, /**< @~chinese ������ݵ�ROI,�ο�DepthRoi            @~english roi of depth data,reference DepthRoi*/
	PROPERTY_EXT_HDR_MODE				= 0x914, /**< @~chinese HDRģʽ                       @~english HDR mode*/
	PROPERTY_EXT_HDR_SCALE_SETTING		= 0x915, /**< @~chinese HDR�Զ�ģʽ������             @~english setting of auto-HDR*/
	PROPERTY_EXT_HDR_EXPOSURE			= 0x916, /**< @~chinese HDR��������                   @~english all params of HDR*/
	PRPOERTY_EXT_MAX_FRAMETIME_GAIN		= 0x917, /**< @~chinese ���֡ʱ�������,�ο�MaxFrameTimeGain              @~english set the max frame and gran,reference MaxFrameTimeGain*/
	PROPERTY_EXT_LASER_BRIGHTNESS		= 0x920, /**< @~chinese ����������                    @~english brightness level of laser*/
	PROPERTY_EXT_LASER_ON_OFF			= 0x922, /**< @~chinese ��������/��                   @~english turn on/off laser*/
	PROPERTY_EXT_SPEED					= 0x924, /**< @~chinese ��ͼ�ٶ�                      @~english speed of shot*/
	
	PROPERTY_EXT_SET_STREAM_RESOLUTION	= 0x702, /**< @~chinese ���÷ֱ���,�ο�StreamResolution                    @~english set resolution of depth stream��reference StreamResolution*/
	PROPERTY_EXT_CONTRAST_MIN			= 0x705, /**< @~chinese �Աȶ���ֵ������ֵ����ɾ��ԭʼͼ���е��ع�����,��ɾ���Ҷȵ��ڸ���ֵ������,��ֵԽ����ع�����ɾ��Խ��.���ڷ�Χ0~40�ҽ�,��������Ϊ5
                                                      @~english remove where fringe contrast below this value*/
	PROPERTY_EXT_ALGO_SET_BACKGROUND	= 0x705, /**< @~chinese ������ֵ,��Χ[0-40],�ο�algoSetBackground @~english background threshold,[0,40]��reference algoSetBackground*/
	PROPERTY_EXT_DEPTH_RANGE			= 0x707, /**< @~chinese ��ȷ�Χ                      @~english depth range of camera*/
	
	PROPERTY_EXT_UNKNOWA00				= 0xa00, /**< @~chinese                 @~english */
	PROPERTY_EXT_MULTIFRAME_FUSION		= 0xa04, /**< @~chinese ��֡�ں�(˫�ع�)��ȡֵ0/1,�ο�multiframeFusion                @~english multiframe fusion,reference multiframeFusion*/
	PROPERTY_EXT_SET_FRINGE_PATTERN		= 0xa05, /**< @~chinese ����pattern�������ο�FRINGE_PATTERN_TYPE  @~english fringe pattern,reference FRINGE_PATTERN_TYPE*/
	PROPERTY_EXT_LED_ON_OFF				= 0xb00, /**< @~chinese �Ƿ��LED��                 @~english turn on/off led*/
	
	
	PROPERTY_EXT_TRIGGER_IN_MODE		= 0x106, /**< @~chinese ����ģʽ                      @~english trigger mode*/
} PROPERTY_TYPE_EXTENSION;
/// @}

/**
* @~chinese
* @brief ��չ����ֵ���������ʾ�����úͻ�ȡʱֻȡָ�����Զ�Ӧ���ֶμ���
* @~english
* @brief union of extensional property
**/
typedef union PropertyExtension
{
	float depthScale;							/**< @~chinese ��ӦPROPERTY_EXT_DEPTH_SCALE			    @~english corresponding PROPERTY_EXT_DEPTH_SCALE			*/
	TRIGGER_MODE triggerMode;					/**< @~chinese ��ӦPROPERTY_EXT_TRIGGER_MODE			@~english corresponding PROPERTY_EXT_TRIGGER_MODE			*/
	int algorithmContrast;						/**< @~chinese ��ӦPROPERTY_EXT_CONTRAST_MIN			@~english corresponding PROPERTY_EXT_CONTRAST_MIN			*/
	AUTO_EXPOSURE_MODE autoExposureMode;		/**< @~chinese ��ӦPROPERTY_EXT_AUTO_EXPOSURE_MODE	    @~english corresponding PROPERTY_EXT_AUTO_EXPOSURE_MODE	*/
	HdrScaleSetting hdrScaleSetting;			/**< @~chinese ��ӦPROPERTY_EXT_HDR_SCALE_SETTING	    @~english corresponding PROPERTY_EXT_HDR_SCALE_SETTING	*/
	HdrExposureSetting hdrExposureSetting;		/**< @~chinese ��ӦPROPERTY_EXT_HDR_EXPOSURE			@~english corresponding PROPERTY_EXT_HDR_EXPOSURE			*/
	int ledOnOff;								/**< @~chinese ��ӦPROPERTY_EXT_LED_ON_OFF			@~english corresponding PROPERTY_EXT_LED_ON_OFF			*/
	
	TRIGGER_MODE triggerInMode;					/**< @~chinese ��ӦPROPERTY_EXT_TRIGGER_OUT_MODE		@~english corresponding PROPERTY_EXT_TRIGGER_OUT_MODE	 */
	int triggerOutEnable;						/**< @~chinese ��ӦPROPERTY_EXT_TRIGGER_IN_MODE		    @~english corresponding PROPERTY_EXT_TRIGGER_IN_MODE	 */
	int laserBrightness;						/**< @~chinese ��ӦPROPERTY_EXT_LASER_BRIGHTNESS		@~english corresponding PROPERTY_EXT_LASER_BRIGHTNESS	 */
	int laserOnOff;								/**< @~chinese ��ӦPROPERTY_EXT_LASER_ON_OFF			@~english corresponding PROPERTY_EXT_LASER_ON_OFF		 */
	int speed;									/**< @~chinese ��ӦPROPERTY_EXT_SPEED				    @~english corresponding PROPERTY_EXT_SPEED				 */
	HdrBrightnessSetting hdrBrightnessSetting;	/**< @~chinese ��ӦPROPERTY_EXT_HDR_BRIGHTNESS		    @~english corresponding PROPERTY_EXT_HDR_BRIGHTNESS		 */

	HDR_MODE hdrMode;							/**< @~chinese ��ӦPROPERTY_EXT_HDR_MODE				@~english corresponding PROPERTY_EXT_HDR_MODE				*/
	DepthRange depthRange;						/**< @~chinese ��ӦPROPERTY_EXT_DEPTH_RANGE			    @~english corresponding PROPERTY_EXT_DEPTH_RANGE			*/
	IpSetting ipSetting;						/**< @~chinese deprecated ��ӦPROPERTY_EXT_IP_SETTING	@~english deprecated corresponding PROPERTY_EXT_IP_SETTING*/
    CameraIpSetting cameraIp;                         /**< @~chinese ��ӦPROPERTY_EXT_CAMERA_IP		    @~english corresponding PROPERTY_EXT_CAMERA_IP*/
    NETWORK_COMPRESS_MODE networkCompressMode;	/**< @~chinese ��ӦPROPERTY_EXT_NETWORK_COMPRESS		@~english corresponding PROPERTY_EXT_NETWORK_COMPRESS	*/
	NetworkingInfo		networkingInfo;			/**< @~chinese ��ӦPROPERTY_EXT_AP_NET_WORKING_INFO/PROPERTY_EXT_TERMINAL_NET_WORKING_INFO		@~english corresponding PROPERTY_EXT_AP_NET_WORKING_INFO/PROPERTY_EXT_TERMINAL_NET_WORKING_INFO	*/
	bool				bFastScanMode;			/**< @~chinese ��ӦPROPERTY_EXT_FAST_SCAN_MODE			@~english corresponding PROPERTY_EXT_FAST_SCAN_MODE	*/
	bool				bHardSyncSwitch;		/**< @~chinese ��ӦPROPERTY_EXT_HARDSYNCSWITCH			@~english corresponding PROPERTY_EXT_HARDSYNCSWITCH	*/
	DepthRgbMatchParam	depthRgbMatchParam;		/**< @~chinese ��ӦPROPERTY_EXT_DEPTH_RGB_MATCH_PARAM	@~english corresponding PROPERTY_EXT_DEPTH_RGB_MATCH_PARAM	*/
	FRINGE_PATTERN_TYPE	fringePatternType;		/**< @~chinese ��ӦPROPERTY_EXT_SET_FRINGE_PATTERN	@~english corresponding PROPERTY_EXT_SET_FRINGE_PATTERN	*/
	int					algoSetBackground;		/**< @~chinese ��ӦPROPERTY_EXT_ALGO_SET_BACKGROUND	@~english corresponding PROPERTY_EXT_ALGO_SET_BACKGROUND	*/
	bool				multiframeFusion;		/**< @~chinese ��ӦPROPERTY_EXT_MULTIFRAME_FUSION	@~english corresponding PROPERTY_EXT_MULTIFRAME_FUSION	*/
	bool				bIsWifiHostMode;		/**< @~chinese ��ӦPROPERTY_EXT_IS_WIFI_HOST_MODE	@~english corresponding PROPERTY_EXT_IS_WIFI_HOST_MODE	*/
	MaxFrameTimeGain	maxFrameTimeGain;		/**< @~chinese ��ӦPRPOERTY_EXT_MAX_FRAMETIME_GAIN	@~english corresponding PRPOERTY_EXT_MAX_FRAMETIME_GAIN	*/
	StreamResolution	streamResolution;		/**< @~chinese ��ӦPROPERTY_EXT_SET_STREAM_RESOLUTION	@~english corresponding PROPERTY_EXT_SET_STREAM_RESOLUTION	*/
	char acSerialNumber[60];					/**< @~chinese ��ӦPROPERTY_EXT_SERIAL_NUMBER	@~english corresponding PROPERTY_EXT_SERIAL_NUMBER	*/
	char acMac[60];								/**< @~chinese ��ӦPROPERTY_EXT_MAC_ADDRESS	@~english corresponding PROPERTY_EXT_MAC_ADDRESS	*/
	DepthRoi	depthRoi;						/**< @~chinese ��ӦPROPERTY_EXT_DEPTH_ROI	@~english corresponding PROPERTY_EXT_DEPTH_ROI	*/
	WriteReadHidData*	writeReadHidData;		/**< @~chinese ��ӦPROPERTY_EXT_WRITE_READ_HID	@~english corresponding PROPERTY_EXT_WRITE_READ_HID	*/
	PerspectiveTransformationMatrix	reconstructionMat; /**< @~chinese ��ӦPROPERTY_EXT_GET_RECONSTRUCTIONMAT	@~english corresponding PROPERTY_EXT_GET_RECONSTRUCTIONMAT	*/

	unsigned int  uiExposureTime;	            /**< @~chinese ��ӦPROPERTY_EXT_EXPOSURE_TIME_RGB �ع�ʱ��,��λ΢��  @~english corresponding PROPERTY_EXT_EXPOSURE_TIME exposure time,unit us*/
	ValueRange objVRange_;						/**< @~chinese ��ӦPROPERTY_EXT_EXPOSURE_TIME_RANGE_RGB �ع�ʱ�䷶Χ,��λ΢��  @~english corresponding PROPERTY_EXT_EXPOSURE_TIME_RANGE exposure time range,unit us*/
	unsigned int uiTempratrue_;					/**< @~chinese ��ӦPROPERTY_EXT_CPU_TEMPRATRUE �¶�,��λ���϶�  @~english corresponding PROPERTY_EXT_CPU_TEMPRATRUE exposure tempratrue,unit degree Celsius*/

	bool boolCameraState;						/**< @~chinese ��ӦPROPERTY_EXT_GET_CAMERA_STATE �����ǰ����״̬  @~english Camera current connect state*/

	bool bSupportGyro;                          /**< @~chinese ��ӦPROPERTY_EXT_IS_SUPPORT_GYRO   @~english corresponding PROPERTY_EXT_IS_SUPPORT_GYRO */
	unsigned short gyroVersion;                 /**< @~chinese ��ӦPROPERTY_EXT_GET_GYRO_VERSION  @~english corresponding PROPERTY_EXT_GET_GYRO_VERSION */

	char reservedStr[60];                       /**< @~chinese Ԥ��									    @~english reserved */
    int reserved[15];							/**< @~chinese Ԥ��									    @~english reserved */
}PropertyExtension;		

#define KEY_INFO_RESERVED_LEN	2

#pragma pack(push, 1)
/**
* @~chinese
* @brief ������Ϣ
* @~english
* @brief key information
**/
typedef struct KeyInfo {
    char   key_num;
	char   key_level;	//KEY_EVENT_DOWN = 0,KEY_EVENT_UP = 1
	char   reserved[KEY_INFO_RESERVED_LEN];	//reserved fot 2 bytes
    int   key_time;		//����ʱ�䣬�ر�˵�����豸�ϵ絽��һ�ΰ���ֵһֱΪ0
}KeyInfo;

/**
* @~chinese
* @brief	������λ�ú�λ��
* @~english
* @brief position and pose of gyro
*/
/*
typedef struct GyroPositionAndPose_tag
{
	float	x;
	float	y;
	float	z;
	float	roll;
	float	pitch;
	float	yaw;
}GyroPositionAndPose;
*/
typedef struct GyroPositionAndPose_tag
{	
	float q0; // w					/**< (q0,q1,q2,q3)->(w,x,y,z): @~chinese ��������̬��ʹ����Ԫ�ر�ʾ  @~english pose of gyro��Use four elements to represent */
	float q1; // x
	float q2; // y
	float q3; // z
	float gx;						/**< @~chinese ��������X��ת�����ٶȣ���λΪ��radian/second   @~english  Gyroscope rotates angular velocity around the X axis, unit: radian/second */
	float gy;						/**< @~chinese  ��������Y��ת�����ٶȣ���λΪ��radian/second   @~english  Gyroscope rotates angular velocity around the Y axis, unit: radian/second */
	float gz;						/**< @~chinese  ��������Z��ת�����ٶȣ���λΪ��radian/second  @~english  Gyroscope rotates angular velocity around the Z axis, unit: radian/second */
	float ax;						/**< @~chinese  ������X������ٶȣ���λΪ��g  @~english  Acceleration in the X direction of the gyroscope, unit: g */
	float ay;						/**< @~chinese  ������Y������ٶȣ���λΪ��g  @~english  Acceleration in the Y direction of the gyroscope, unit: g */
	float az;						/**< @~chinese  ������Z������ٶȣ���λΪ��g  @~english  Acceleration in the Z direction of the gyroscope, unit: g */
	float mx;						/**< @~chinese  ������X����ų�����λΪ��uT  @~english  The magnetic field in the X direction of the gyroscope, unit: uT */
	float my;						/**< @~chinese  ������Y����ų�����λΪ��uT  @~english  The magnetic field in the Y direction of the gyroscope, unit: uT */
	float mz;						/**< @~chinese  ������Z����ų�����λΪ��uT  @~english  The magnetic field in the Z direction of the gyroscope, unit: uT */
	float score;					/**< @~chinese  �˶���������ΧΪ��[0-1], ��ֵԽ��Խ�ȶ�  @~english  Sports score, the range is: [0-1], the larger the value, the more stable */
}GyroPositionAndPose;

#define ADDITION_RESERVED_LEN	8
#define ADDITION_RESERVED_LEN2	4

typedef struct AdditionData
{
    char    reserved[ADDITION_RESERVED_LEN];
    KeyInfo keyInfo;
    char    reserved2[ADDITION_RESERVED_LEN2];
    int     timestamp;
	GyroPositionAndPose	gyroPosAndPos;
}AdditionData;

#define EXTRA_INFO_RESERVED_LEN	24

/**
* @~chinese
* @brief ֡�ĸ�������
* @~english
* @brief extra information of frame
**/
typedef union ExtraInfo
{
    AdditionData addition;
    char reserved[EXTRA_INFO_RESERVED_LEN];
}ExtraInfo;
#pragma pack(pop)

/**
* @~chinese
* @brief ����Ϣ��ϣ����ڴ���ʱʹ�ã���ͨ��ICamera::getStreamInfos���
* @~english
* @brief stream information, returned by ICamera::getStreamInfos
**/
typedef struct StreamInfo
{
	STREAM_FORMAT format;	/**< @~chinese ����Ϣ         @~english stream format*/ 
	int width;				/**< @~chinese ���           @~english stream width*/
	int height;				/**< @~chinese �߶�           @~english stream height*/
	float fps;				/**< @~chinese ֡��           @~english stream framerate*/
}StreamInfo;

/**
* @~chinese
* @brief �����Ϣ����ͨ��ICamera::getInfo��ISystem::queryCameras���
* @~english
* @brief camera informations, returned by ICamera::getStreamInfos or ISystem::queryCameras
**/
typedef struct CameraInfo
{
	char name[32];					/**< @~chinese �������         @~english type of camera*/ 
	char serial[CAMERA_SERIAL_MAX];				/**< @~chinese ���к�           @~english serial number of camera*/
	char uniqueId[32];				/**< @~chinese �����ʶ         @~english unique Id of camera*/
	char firmwareVersion[FIRMWARE_VERSION_MAX];		/**< @~chinese �̼��汾         @~english version of firmware*/
	char algorithmVersion[ALGORITHM_VERSION_MAX];		/**< @~chinese �㷨�汾         @~english version of algorithm*/
}CameraInfo;

/**
* @~chinese
* @brief ����ڲ�
* @~english
* @brief Intrinsics of depth camera or RGB camera
**/
typedef struct Intrinsics
{
	short width;	/**< @~chinese �궨�ֱ���-���		@~english calibration resolution-width*/ 
	short height;	/**< @~chinese �궨�ֱ���-�߶�		@~english calibration resolution-height*/ 
	float fx;
	float zero01;
	float cx;
	float zeor10;
	float fy;
	float cy;
	float zeor20;
	float zero21;
	float one22;
}Intrinsics;

/**
* @~chinese
* @brief ��������RGB��������תƽ����Ϣ
* @~english
* @brief Rotation and translation offrom depth camera to RGB camera
**/
typedef struct Extrinsics
{
	float rotation[9];                           /**<@~chinese 3x3��ת����      @~english column-major 3x3 rotation matrix */
	float translation[3];                        /**<@~chinese 3Ԫ�ص�ƽ�ƾ���  @~english three-element translation vector */
}Extrinsics;

//�����������
#define DISTORT_PARAM_CNT	5

/**
* @~chinese
* @brief ��������RGB����������
* @~english
* @brief Distort of depth camera or RGB camera
**/
typedef struct Distort
{
	float k1;
	float k2;
	float k3;
	float k4;
	float k5;
}Distort;




#ifdef __cplusplus
}
#endif

namespace cs {
	/**
	* @~chinese
	* @brief ��ά������
	* @~english
	* @brief 2D point coordinates
	**/
#ifndef POINT2F
#define POINT2F
	typedef struct Point2f
	{
		float x;
		float y;
	} Point2f;
#endif
	/**
	* @~chinese
	* @brief ��ά������
	* @~english
	* @brief 3D point coordinates
	**/
#ifndef POINT3F
#define POINT3F
	typedef struct Point3f
	{
		float x;
		float y;
		float z;
	} Point3f;
#endif
}

#endif
