#pragma once

#include <string>

namespace Good
{
	namespace ShaderVocalubary
	{
		namespace Scalars
		{
			// Scalars
			const std::string Bool = "bool";
			const std::string Int = "int";
			const std::string UInt = "uint";
			const std::string Float = "float";
			const std::string Double = "double";
		}

		namespace Vectors
		{
			// Vectors
			std::string Bool(int lenght){ return "bvec" + std::to_string(lenght); }
			std::string Int(int lenght){ return "ivec" + std::to_string(lenght); }
			std::string UInt(int lenght){ return "uvec" + std::to_string(lenght); }
			std::string Float(int lenght){ return "vec" + std::to_string(lenght); }
			std::string Double(int lenght){ return "dvec" + std::to_string(lenght); }
		}

		namespace Matrices
		{
			// Vectors
			std::string Rectangular(int column, int row){ return "mat" + std::to_string(column) + "x" + std::to_string(row); }
			std::string Square(int lenght){ return "mat" + std::to_string(lenght); }
		}

		namespace Samplers
		{
			// Samplers
			const std::string  SamplerTexture1D = "sampler1D";
			const std::string  SamplerTexture2D = "sampler2D";
			const std::string  SamplerTexture3D = "sampler3D";
			const std::string  SamplerTexture2DRect = "sampler2DRect";
			const std::string  SamplerTexture1DArray = "sampler1DArray";
			const std::string  SamplerTexture2DArray = "sampler2DArray";
			const std::string  SamplerTextureCube = "samplerCube";
			const std::string  SamplerTextureCubeArray = "samplerCubeArray";
			const std::string  SamplerTextureBuffer = "samplerBuffer";
			const std::string  SamplerTexture2DMultiSample = "sampler2DMS";
			const std::string  SamplerTexture2DMultiSampleArray = "sampler2DMSArray";
		}
	}

	namespace ShaderFrameWork
	{
	}
}