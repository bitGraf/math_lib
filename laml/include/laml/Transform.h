#ifndef __TRANSFORM_H
#define __TRANSFORM_H

#include <laml/Vector.hpp>
#include <laml/Matrix.hpp>
#include <laml/Quaternion.hpp>

namespace laml {
    namespace transform {
        
        void create_projection_orthographic(Matrix4x4& mat, real_t left, real_t right, real_t bottom, real_t top, real_t znear, real_t zfar);
        void create_projection_perspective(Matrix4x4& mat, real_t vertical_fov, real_t aspect_ratio, real_t znear, real_t zfar);
        void create_view_matrix_from_transform(Matrix4x4& view, const Matrix4x4& transform);

        Vector2 transform_point(const Matrix2x2& mat, const Vector2& vec);
        Vector3 transform_point(const Matrix3x3& mat, const Vector3& vec);
        Vector4 transform_point(const Matrix4x4& mat, const Vector4& vec);
        Vector3 transform_point(const Matrix4x4& mat, const Vector3& vec, real_t w);

        // convert to quaternion
        Quaternion quat_from_mat(const Matrix3x3& mat);

        // Create various 4x4 transformation matrices
        void create_transform_rotation(Matrix4x4& mat, real_t yaw, real_t pitch, real_t roll);
        void create_transform_rotation(Matrix3x3& mat, real_t yaw, real_t pitch, real_t roll);
        void create_ZXZ_rotation(Matrix3x3& mat, real_t alpha, real_t beta, real_t gamma);
        void create_transform_rotation(Matrix4x4& mat, const Quaternion& rot_quat);
        void create_transform_rotation(Matrix3x3& mat, const Quaternion& rot_quat);

        void create_transform_scale(Matrix4x4& mat, real_t x_scale, real_t y_scale, real_t z_scale);
        void create_transform_scale(Matrix4x4& mat, const Vector3& scale_vec);

        void create_transform_translate(Matrix4x4& mat, real_t x_trans, real_t y_trans, real_t z_trans);
        void create_transform_translate(Matrix4x4& mat, const Vector3& trans_vec);

        // Basic order of arguments is always rotation,translation,scale
        // If any component is missed, it is assumed "identity"
        void create_transform(Matrix4x4& mat, const Matrix4x4& rot_mat, const Matrix4x4& trans_mat, const Matrix4x4& scale_mat);
        void create_transform(Matrix4x4& mat, const Matrix4x4& rot_mat, const Matrix4x4& trans_mat);

        void create_transform(Matrix4x4& mat, real_t rot_yaw, real_t rot_pitch, real_t rot_roll, const Vector3& trans_vec, const Vector3& scale_vec);
        void create_transform(Matrix4x4& mat, const Matrix3x3& rot_mat3, const Vector3& trans_vec, const Vector3& scale_vec);
        void create_transform(Matrix4x4& mat, const Quaternion& rot_quat, const Vector3& trans_vec, const Vector3& scale_vec);

        void create_transform(Matrix4x4& mat, real_t rot_yaw, real_t rot_pitch, real_t rot_roll, const Vector3& trans_vec);
        void create_transform(Matrix4x4& mat, const Matrix3x3& rot_mat3, const Vector3& trans_vec);
        void create_transform(Matrix4x4& mat, const Quaternion& rot_quat, const Vector3& trans_vec);


        laml::Quat quat_from_axis_angle(const laml::Vec3& axis, real_t angle);
        laml::Quat quat_from_ypr(real_t yaw, real_t pitch, real_t roll);
        laml::Vec3 dir_from_yp(real_t yaw, real_t pitch);

        //template<typename real_t>
        //void create_transform(Matrix4x4& mat, const Matrix3x3& rot_mat3, const Vector3& trans_vec) {}
        //template<typename real_t>
        //void create_transform(Matrix4x4& mat, const Quaternion& rot_quat, const Vector3& trans_vec) {}


        // Decompose 4x4 transformations into their components
        //math::Decompose(transformComponent->Transform, position, Forward, Right, Up, yaw, pitch, scale);
	
        bool decompose(const Matrix4x4& transform,
                       Matrix3x3& rot_mat, Vector3& trans_vec, Vector3& scale_vec);
        void decompose(const Matrix4x4& mat,
                       Vector3& trans_vec,
                       Vector3& forward_vec, Vector3& right_vec, Vector3& up_vec,
                       real_t& rot_yaw, real_t& rot_pitch, real_t& rot_roll,
                       Vector3& scale_vec);
        void decompose(const Matrix4x4& mat,
                       Vector3& trans_vec,
                       Vector3& forward_vec, Vector3& right_vec, Vector3& up_vec,
                       real_t& rot_yaw, real_t& rot_pitch,
                       Vector3& scale_vec);
        void decompose(const Matrix4x4& mat,
                       Vector3& forward_vec, Vector3& right_vec, Vector3& up_vec);
        void decompose(const Matrix4x4& mat,
                       real_t& rot_yaw, real_t& rot_pitch, real_t& rot_roll);

        // calculates a transform matrix that puts the obj at 'start' and looks at 'target'
        // note: this returns a transformation matrix, not a view matrix.
        //       use create_view_matrix_from_transform() if you need that
        void lookAt(Matrix4x4& transform, const Vector3& start, const Vector3& target, const Vector3& ref_up);
    }
}

#endif