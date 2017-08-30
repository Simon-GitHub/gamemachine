// 阴影纹理
uniform sampler2DShadow GM_shadow_texture;
uniform int GM_shadow_texture_switch = 0;

#define MAX_TEXTURE_COUNT 3
#define MAX_LIGHT_COUNT 10
struct GM_texture_t
{
	sampler2D texture;
	float scroll_s;
	float scroll_t;
	float scale_s;
	float scale_t;
	int enabled;
};
uniform GM_texture_t GM_ambient_textures[MAX_TEXTURE_COUNT];
uniform GM_texture_t GM_diffuse_textures[MAX_TEXTURE_COUNT];
uniform GM_texture_t GM_lightmap_textures[MAX_TEXTURE_COUNT];  // 用到的只有1个
uniform GM_texture_t GM_normalmap_textures[1];

struct GM_light_t
{
	vec3 lightColor;
	vec3 lightPosition;
};
uniform GM_light_t GM_ambients[MAX_LIGHT_COUNT];
uniform GM_light_t GM_speculars[MAX_LIGHT_COUNT];

struct GM_Material_t
{
	vec3 ka;
	vec3 kd;
	vec3 ks;
	float shininess;
};
uniform GM_Material_t GM_material;