#include <laml/Transform.hpp>

#include <laml/Functions.hpp>
#include <laml/Constants.hpp>

namespace laml {
    namespace transform {
        
        void create_projection_orthographic(Matrix4x4& mat, real_t left, real_t right, real_t bottom, real_t top, real_t znear, real_t zfar) {
            laml::fill(mat, 0.0);

            mat[0][0] =  2.0 / (right - left);
            mat[1][1] =  2.0 / (top - bottom);
            mat[2][2] = -2.0 / (zfar - znear);

            mat[3][0] = -(right + left) / (right - left);
            mat[3][1] = -(top + bottom) / (top - bottom);
            mat[3][2] = -(zfar + znear) / (zfar - znear);

            mat[3][3] = 1.0;
        }

        void create_projection_perspective(Matrix4x4& mat, real_t vertical_fov, real_t aspect_ratio, real_t znear, real_t zfar) {
            laml::fill(mat, 0.0);

            //const real_t tan_half = static_cast<real_t>(tan(vertical_fov * constants::deg2rad / 2.0));
            const real_t tan_half = tan(vertical_fov * constants::deg2rad / 2.0);

            mat[0][0] = 1.0 / (aspect_ratio * tan_half);
            mat[1][1] = 1.0 / tan_half;
            mat[2][2] = -(zfar + znear) / (zfar - znear);
            mat[2][3] = -1.0;
            mat[3][2] = -2.0 * zfar * znear / (zfar - znear);
        }

        void create_view_matrix_from_transform(Matrix4x4& view, const Matrix4x4& transform) {
            // assume no scale is applied to the camera transform!!
            // V = inv(real_t x R) = inv(R) x inv(real_t) = transpose(R) x (-real_t)
            Matrix4x4 inv_rot(laml::transpose(transform));
            inv_rot.c_41 = 0.0;
            inv_rot.c_42 = 0.0;
            inv_rot.c_43 = 0.0;
            Matrix4x4 inv_translate(1.0);
            inv_translate.c_14 = -transform.c_14;
            inv_translate.c_24 = -transform.c_24;
            inv_translate.c_34 = -transform.c_34;
            view = mul(inv_rot, inv_translate);
        }

        Vector2 transform_point(const Matrix2x2& mat, const Vector2& vec) {
            Vector2 res;
            for (size_t i = 0; i < 2; i++) {
                res[i] = 0.0;
                for (size_t j = 0; j < 2; j++) {
                    res[i] = res[i] + vec[j] * mat[j][i];
                }
            }
            return res;
        }

        Vector3 transform_point(const Matrix3x3& mat, const Vector3& vec) {
            Vector3 res;
            for (size_t i = 0; i < 3; i++) {
                res[i] = 0.0;
                for (size_t j = 0; j < 3; j++) {
                    res[i] = res[i] + vec[j] * mat[j][i];
                }
            }
            return res;
        }

        Vector3 transform_point(const Matrix4x4& mat, const Vector3& vec, real_t w) {
            Vector3 res(
                mat.c_11 * vec.x + mat.c_12 * vec.y + mat.c_13 * vec.z + mat.c_14 * w,
                mat.c_21 * vec.x + mat.c_22 * vec.y + mat.c_23 * vec.z + mat.c_24 * w,
                mat.c_31 * vec.x + mat.c_32 * vec.y + mat.c_33 * vec.z + mat.c_34 * w);
            return res;
        }
        Vector4 transform_point(const Matrix4x4& mat, const Vector4& vec) {
            Vector4 res(
                mat.c_11 * vec.x + mat.c_12 * vec.y + mat.c_13 * vec.z + mat.c_14 * vec.w,
                mat.c_21 * vec.x + mat.c_22 * vec.y + mat.c_23 * vec.z + mat.c_24 * vec.w,
                mat.c_31 * vec.x + mat.c_32 * vec.y + mat.c_33 * vec.z + mat.c_34 * vec.w,
                mat.c_41 * vec.x + mat.c_42 * vec.y + mat.c_43 * vec.z + mat.c_44 * vec.w);
            return res;
        }

        // convert to quaternion
        Quaternion quat_from_mat(const Matrix3x3& mat) {
            const real_t one  = 1.0;
            const real_t two  = 2.0;
            const real_t four = 4.0;
            const real_t one_fourth = one / four;
            real_t tr = trace(mat);
            Quaternion res;
            if (tr > 0) {
                real_t S = sqrt(tr + one) * two; // S = 4*qw
                res.w = one_fourth * S;
                res.x = (mat.c_32 - mat.c_23) / S;
                res.y = (mat.c_13 - mat.c_31) / S;
                res.z = (mat.c_21 - mat.c_12) / S;
            }
            else if ((mat.c_11 > mat.c_22) && (mat.c_11 > mat.c_33)) {
                real_t S = sqrt(one + mat.c_11 - mat.c_22 - mat.c_33) * two; // S = 4*qx
                res.w = (mat.c_32 - mat.c_23) / S;
                res.x = one_fourth * S;
                res.y = (mat.c_12 + mat.c_21) / S;
                res.z = (mat.c_13 + mat.c_31) / S;
            }
            else if (mat.c_22 > mat.c_33) {
                real_t S = sqrt(one + mat.c_22 - mat.c_11 - mat.c_33) * two; // S = 4*qy
                res.w = (mat.c_13 - mat.c_31) / S;
                res.x = (mat.c_12 + mat.c_21) / S;
                res.y = one_fourth * S;
                res.z = (mat.c_23 + mat.c_32) / S;
            }
            else {
                real_t S = sqrt(one + mat.c_33 - mat.c_11 - mat.c_22) * two; // S = 4*qz
                res.w = (mat.c_21 - mat.c_12) / S;
                res.x = (mat.c_13 + mat.c_31) / S;
                res.y = (mat.c_23 + mat.c_32) / S;
                res.z = one_fourth * S;
            }
            return res;
        }

        // Create various 4x4 transformation matrices
        void create_transform_rotation(Matrix4x4& mat, real_t yaw, real_t pitch, real_t roll) {
            real_t C1, C2, C3, S1, S2, S3;
            C1 = cosf(yaw   * constants::deg2rad);
            C2 = cosf(pitch * constants::deg2rad);
            C3 = cosf(roll  * constants::deg2rad);
            S1 = sinf(yaw   * constants::deg2rad);
            S2 = sinf(pitch * constants::deg2rad);
            S3 = sinf(roll  * constants::deg2rad);

            mat = Matrix4x4(1.0); // create identity matrix
            mat[0][0] =  C1 * C3 - S1 * S2 * S3;
            mat[0][1] = -C2 * S3;
            mat[0][2] = -S1 * C3 - C1 * S2 * S3;

            mat[1][0] =  C1 * S3 + S1 * S2 * C3;
            mat[1][1] =  C2 * C3;
            mat[1][2] = -S1 * S3 + C1 * S2 * C3;

            mat[2][0] =  S1 * C2;
            mat[2][1] = -S2;
            mat[2][2] =  C1 * C2;
        }
        void create_transform_rotation(Matrix3x3& mat, real_t yaw, real_t pitch, real_t roll) {
            real_t C1, C2, C3, S1, S2, S3;
            C1 = cos(yaw   * constants::deg2rad);
            C2 = cos(pitch * constants::deg2rad);
            C3 = cos(roll  * constants::deg2rad);
            S1 = sin(yaw   * constants::deg2rad);
            S2 = sin(pitch * constants::deg2rad);
            S3 = sin(roll  * constants::deg2rad);

            mat = Matrix3x3(1.0); // create identity matrix
            mat[0][0] =  C1 * C3 - S1 * S2 * S3;
            mat[0][1] = -C2 * S3;
            mat[0][2] = -S1 * C3 - C1 * S2 * S3;

            mat[1][0] =  C1 * S3 + S1 * S2 * C3;
            mat[1][1] =  C2 * C3;
            mat[1][2] = -S1 * S3 + C1 * S2 * C3;

            mat[2][0] =  S1 * C2;
            mat[2][1] = -S2;
            mat[2][2] =  C1 * C2;
        }
        void create_ZXZ_rotation(Matrix3x3& mat, real_t alpha, real_t beta, real_t gamma) {
            real_t C1, C2, C3, S1, S2, S3;
            C1 = cosd(alpha);
            C2 = cosd(beta);
            C3 = cosd(gamma);
            S1 = sind(alpha);
            S2 = sind(beta);
            S3 = sind(gamma);

            // mat[j][i] = c_ij (zero-indexed)
            mat = Matrix3x3(1.0); // create identity matrix
            mat[0][0] = C1*C3 - S1*C2*S3;
            mat[0][1] = S1*C3 + C1*C2*S3;
            mat[0][2] = S2*S3;

            mat[1][0] = -C1*S3 - S1*C2*C3;
            mat[1][1] =  C1*C2*C3 - S1*S3;
            mat[1][2] =  S2*C3;

            mat[2][0] =  S1*S2;
            mat[2][1] = -C1*S2;
            mat[2][2] =  C2;
        }
        void create_transform_rotation(Matrix4x4& mat, const Quaternion& rot_quat) {
            mat = Matrix4x4(1.0);
            mat[0][0] = 1 - 2 * (rot_quat.y * rot_quat.y) - 2 * (rot_quat.z * rot_quat.z);
            mat[0][1] = 2 * (rot_quat.x * rot_quat.y + rot_quat.z * rot_quat.w);
            mat[0][2] = 2 * (rot_quat.z * rot_quat.x - rot_quat.y * rot_quat.w);
            mat[1][0] = 2 * (rot_quat.x * rot_quat.y - rot_quat.z * rot_quat.w);
            mat[1][1] = 1 - 2 * (rot_quat.z * rot_quat.z) - 2 * (rot_quat.x * rot_quat.x);
            mat[1][2] = 2 * (rot_quat.y * rot_quat.z + rot_quat.x * rot_quat.w);
            mat[2][0] = 2 * (rot_quat.z * rot_quat.x + rot_quat.y * rot_quat.w);
            mat[2][1] = 2 * (rot_quat.y * rot_quat.z - rot_quat.x * rot_quat.w);
            mat[2][2] = 1 - 2 * (rot_quat.x * rot_quat.x) - 2 * (rot_quat.y * rot_quat.y);
        }
        void create_transform_rotation(Matrix3x3& mat, const Quaternion& rot_quat) {
            mat = Matrix3x3(1.0);
            mat[0][0] = 1 - 2 * (rot_quat.y * rot_quat.y) - 2 * (rot_quat.z * rot_quat.z);
            mat[0][1] = 2 * (rot_quat.x * rot_quat.y + rot_quat.z * rot_quat.w);
            mat[0][2] = 2 * (rot_quat.z * rot_quat.x - rot_quat.y * rot_quat.w);
            mat[1][0] = 2 * (rot_quat.x * rot_quat.y - rot_quat.z * rot_quat.w);
            mat[1][1] = 1 - 2 * (rot_quat.z * rot_quat.z) - 2 * (rot_quat.x * rot_quat.x);
            mat[1][2] = 2 * (rot_quat.y * rot_quat.z + rot_quat.x * rot_quat.w);
            mat[2][0] = 2 * (rot_quat.z * rot_quat.x + rot_quat.y * rot_quat.w);
            mat[2][1] = 2 * (rot_quat.y * rot_quat.z - rot_quat.x * rot_quat.w);
            mat[2][2] = 1 - 2 * (rot_quat.x * rot_quat.x) - 2 * (rot_quat.y * rot_quat.y);
        }

        void create_transform_scale(Matrix4x4& mat, real_t x_scale, real_t y_scale, real_t z_scale) {
            mat = Matrix4x4(x_scale, y_scale, z_scale, 1.0);
        }
        void create_transform_scale(Matrix4x4& mat, const Vector3& scale_vec) {
            mat = Matrix4x4(scale_vec.x, scale_vec.y, scale_vec.z, 1.0);
        }

        void create_transform_translate(Matrix4x4& mat, real_t x_trans, real_t y_trans, real_t z_trans) {
            mat = Matrix4x4(1.0);
            mat.c_14 = x_trans;
            mat.c_24 = y_trans;
            mat.c_34 = z_trans;
        }
        void create_transform_translate(Matrix4x4& mat, const Vector3& trans_vec) {
            mat = Matrix4x4(1.0);
            mat.c_14 = trans_vec.x;
            mat.c_24 = trans_vec.y;
            mat.c_34 = trans_vec.z;
        }

        // Basic order of arguments is always rotation,translation,scale
        // If any component is missed, it is assumed "identity"
        void create_transform(Matrix4x4& mat, const Matrix4x4& rot_mat, const Matrix4x4& trans_mat, const Matrix4x4& scale_mat) {
            mat = mul(mul(trans_mat, rot_mat), scale_mat);
        }
        void create_transform(Matrix4x4& mat, const Matrix4x4& rot_mat, const Matrix4x4& trans_mat) {
            mat = mul(trans_mat, rot_mat);
        }

        void create_transform(Matrix4x4& mat, real_t rot_yaw, real_t rot_pitch, real_t rot_roll, const Vector3& trans_vec, const Vector3& scale_vec) {
            Matrix4x4 rot_mat, trans_mat, scale_mat;

            create_transform_rotation(rot_mat, rot_yaw, rot_pitch, rot_roll);
            create_transform_translate(trans_mat, trans_vec);
            create_transform_scale(scale_mat, scale_vec);

            create_transform(mat, rot_mat, trans_mat, scale_mat);
        }
        void create_transform(Matrix4x4& mat, const Matrix3x3& rot_mat3, const Vector3& trans_vec, const Vector3& scale_vec) {
            Matrix4x4 trans_mat, scale_mat;

            Matrix4x4 rot_mat(rot_mat3);
            create_transform_translate(trans_mat, trans_vec);
            create_transform_scale(scale_mat, scale_vec);

            create_transform(mat, rot_mat, trans_mat, scale_mat);
        }
        void create_transform(Matrix4x4& mat, const Quaternion& rot_quat, const Vector3& trans_vec, const Vector3& scale_vec) {
            Matrix4x4 rot_mat, trans_mat, scale_mat;

            create_transform_rotation(rot_mat, rot_quat);
            create_transform_translate(trans_mat, trans_vec);
            create_transform_scale(scale_mat, scale_vec);

            create_transform(mat, rot_mat, trans_mat, scale_mat);
        }

        void create_transform(Matrix4x4& mat, real_t rot_yaw, real_t rot_pitch, real_t rot_roll, const Vector3& trans_vec) {
            Matrix4x4 rot_mat, trans_mat;

            create_transform_rotation(rot_mat, rot_yaw, rot_pitch, rot_roll);
            create_transform_translate(trans_mat, trans_vec);

            create_transform(mat, rot_mat, trans_mat);
        }
        void create_transform(Matrix4x4& mat, const Matrix3x3& rot_mat3, const Vector3& trans_vec) {
            Matrix4x4 trans_mat;

            Matrix4x4 rot_mat(rot_mat3);
            create_transform_translate(trans_mat, trans_vec);

            create_transform(mat, rot_mat, trans_mat);
        }
        void create_transform(Matrix4x4& mat, const Quaternion& rot_quat, const Vector3& trans_vec) {
            Matrix4x4 rot_mat, trans_mat;

            create_transform_rotation(rot_mat, rot_quat);
            create_transform_translate(trans_mat, trans_vec);

            create_transform(mat, rot_mat, trans_mat);
        }


        laml::Quat quat_from_axis_angle(const laml::Vec3& axis, real_t angle) {
            // angle in degrees
            real_t half_angle = angle * 0.5;
            real_t c = laml::cosd(half_angle);
            real_t s = laml::sind(half_angle);

            laml::Quat ret(s*axis.x, s*axis.y, s*axis.z, c);

            return laml::normalize(ret);
        }

        laml::Quat quat_from_ypr(real_t yaw, real_t pitch, real_t roll) {
            // angles in degrees

            laml::Mat3 rot_mat;
            laml::transform::create_transform_rotation(rot_mat, yaw, pitch, roll);

            laml::Quat ret = laml::transform::quat_from_mat(rot_mat);

            return laml::normalize(ret);
        }

        laml::Vec3 dir_from_yp(real_t yaw, real_t pitch) {
            // angles in degrees

            laml::Mat3 rot_mat;
            laml::transform::create_transform_rotation(rot_mat, yaw, pitch, 0.0);
            return -laml::normalize(rot_mat[2]); // forward is -Z
        }

        //template<typename real_t>
        //void create_transform(Matrix4x4& mat, const Matrix3x3& rot_mat3, const Vector3& trans_vec) {}
        //template<typename real_t>
        //void create_transform(Matrix4x4& mat, const Quaternion& rot_quat, const Vector3& trans_vec) {}


        // Decompose 4x4 transformations into their components
        //math::Decompose(transformComponent->Transform, position, Forward, Right, Up, yaw, pitch, scale);
	
        bool decompose(const Matrix4x4& transform,
                       Matrix3x3& rot_mat, Vector3& trans_vec, Vector3& scale_vec) {

            Matrix4x4 local_matrix(transform); // local copy
            //ENGINE_LOG_DEBUG("local_matrix = {0}", local_matrix);

            // first check if mat[3][3] != 0;
            real_t eps = static_cast<real_t>(1e-10);
            if (laml::epsilon_equal(local_matrix.c_44, static_cast<real_t>(0.0), eps)) {
                return false;
            }

            // assume matrix is already "normalized" i.e. w=1.0
            if (!laml::epsilon_equal(local_matrix.c_44, static_cast<real_t>(1.0), eps)) {
                //assert(laml::epsilon_equal(local_matrix.c_44, 1.0, eps) && "Transformation matrix non-standard!");
                local_matrix = local_matrix / local_matrix.c_44;
            }

            // Ignore perspective
            //assert(
            //    epsilon_equal(local_matrix.c_41, 0.0, eps) &&
            //    epsilon_equal(local_matrix.c_42, 0.0, eps) &&
            //    epsilon_equal(local_matrix.c_43, 0.0, eps) &&
            //    "Transformation has perspective elements!");

            // extract Translation
            trans_vec.x = local_matrix.c_14;
            trans_vec.y = local_matrix.c_24;
            trans_vec.z = local_matrix.c_34;

            local_matrix.c_14 = 0.0;
            local_matrix.c_24 = 0.0;
            local_matrix.c_34 = 0.0;

            //ENGINE_LOG_DEBUG("pos_vec = {0}", trans_vec);
            //ENGINE_LOG_DEBUG("local_matrix = {0}", local_matrix);

            // extract scale and shear
            Matrix3x3 mat = laml::minor(local_matrix, 3, 3);

            // compute x scale factor and normalize first column
            scale_vec.x = laml::length(mat._cols[0]);
            mat._cols[0] = laml::normalize(mat._cols[0]);
            //ENGINE_LOG_DEBUG("local_matrix = {0}", mat);

            // compute y scale factor and normalize second column
            scale_vec.y = laml::length(mat._cols[1]);
            mat._cols[1] = laml::normalize(mat._cols[1]);
            //ENGINE_LOG_DEBUG("local_matrix = {0}", mat);

            // compute z scale factor and normalize third column
            scale_vec.z = laml::length(mat._cols[2]);
            mat._cols[2] = laml::normalize(mat._cols[2]);
            //ENGINE_LOG_DEBUG("local_matrix = {0}", mat);

            //ENGINE_LOG_DEBUG("scale_vec = {0}", scale_vec);
            //ENGINE_LOG_DEBUG("local_matrix = {0}", mat);

            // what remains should be a pure rotation 3x3!
            //ENGINE_LOG_DEBUG("rot_33 = {0}", mat);
            rot_mat = mat;

            return true;
        }

        void decompose(const Matrix4x4& mat,
                       Vector3& trans_vec,
                       Vector3& forward_vec, Vector3& right_vec, Vector3& up_vec,
                       real_t& rot_yaw, real_t& rot_pitch, real_t& rot_roll,
                       Vector3& scale_vec) {

            Matrix3x3 rot_mat;
            //Vector3 trans_vec;
            //Vector3 scale_vec;
            decompose(mat, rot_mat, trans_vec, scale_vec);

            // Right: +X
            right_vec.x = rot_mat.c_11;
            right_vec.y = rot_mat.c_21;
            right_vec.z = rot_mat.c_31;
            // Up: +Y
            up_vec.x = rot_mat.c_12;
            up_vec.y = rot_mat.c_22;
            up_vec.z = rot_mat.c_32;
            // Forward: -Z
            forward_vec.x = -rot_mat.c_13;
            forward_vec.y = -rot_mat.c_23;
            forward_vec.z = -rot_mat.c_33;

            // ypr
            rot_pitch = asin(-rot_mat.c_23) * constants::rad2deg;
            rot_yaw   = atan2(rot_mat.c_13, rot_mat.c_33) * constants::rad2deg;
            rot_roll  = atan2(-rot_mat.c_21, rot_mat.c_22) * constants::rad2deg;
        }

        void decompose(const Matrix4x4& mat,
                       Vector3& trans_vec,
                       Vector3& forward_vec, Vector3& right_vec, Vector3& up_vec,
                       real_t& rot_yaw, real_t& rot_pitch,
                       Vector3& scale_vec) {

            Matrix3x3 rot_mat;
            //Vector3 trans_vec;
            //Vector3 scale_vec;
            decompose(mat, rot_mat, trans_vec, scale_vec);

            // Right: +X
            right_vec.x = rot_mat.c_11;
            right_vec.y = rot_mat.c_21;
            right_vec.z = rot_mat.c_31;
            // Up: +Y
            up_vec.x = rot_mat.c_12;
            up_vec.y = rot_mat.c_22;
            up_vec.z = rot_mat.c_32;
            // Forward: -Z
            forward_vec.x = -rot_mat.c_13;
            forward_vec.y = -rot_mat.c_23;
            forward_vec.z = -rot_mat.c_33;

            // ypr
            rot_pitch = asin(-rot_mat.c_23) * constants::rad2deg;
            rot_yaw = atan2(rot_mat.c_13, rot_mat.c_33) * constants::rad2deg;
        }

        void decompose(const Matrix4x4& mat,
                       Vector3& forward_vec, Vector3& right_vec, Vector3& up_vec) {

            Matrix3x3 rot_mat;
            Vector3 trans_vec;
            Vector3 scale_vec;
            decompose(mat, rot_mat, trans_vec, scale_vec);

            // Right: +X
            right_vec.x = rot_mat.c_11;
            right_vec.y = rot_mat.c_21;
            right_vec.z = rot_mat.c_31;
            // Up: +Y
            up_vec.x = rot_mat.c_12;
            up_vec.y = rot_mat.c_22;
            up_vec.z = rot_mat.c_32;
            // Forward: -Z
            forward_vec.x = -rot_mat.c_13;
            forward_vec.y = -rot_mat.c_23;
            forward_vec.z = -rot_mat.c_33;
        }

        void decompose(const Matrix4x4& mat,
                       real_t& rot_yaw, real_t& rot_pitch, real_t& rot_roll) {

            Matrix3x3 rot_mat;
            Vector3 trans_vec;
            Vector3 scale_vec;
            decompose(mat, rot_mat, trans_vec, scale_vec);

            // ypr
            rot_pitch = asin(-rot_mat.c_23) * constants::rad2deg;
            rot_yaw = atan2(rot_mat.c_13, rot_mat.c_33) * constants::rad2deg;
            rot_roll = atan2(-rot_mat.c_21, rot_mat.c_22) * constants::rad2deg;
        }

        // calculates a transform matrix that puts the obj at 'start' and looks at 'target'
        // note: this returns a transformation matrix, not a view matrix.
        //       use create_view_matrix_from_transform() if you need that
        void lookAt(Matrix4x4& transform, const Vector3& start, const Vector3& target, const Vector3& ref_up) {
            Vector3 forward = laml::normalize(target - start);
            Vector3 right   = laml::normalize(laml::cross(forward, ref_up));
            Vector3 up      = laml::normalize(laml::cross(right, forward));

            laml::identity(transform);
            transform.c_11 = right.x;
            transform.c_21 = right.y;
            transform.c_31 = right.z;

            transform.c_12 = up.x;
            transform.c_22 = up.y;
            transform.c_32 = up.z;

            transform.c_13 = -forward.x;
            transform.c_23 = -forward.y;
            transform.c_33 = -forward.z;

            transform.c_14 = start.x;
            transform.c_24 = start.y;
            transform.c_34 = start.z;

            /* glm::lookAt() -> returns a view matrix
            Vector3 f = laml::normalize(center - eye);
            Vector3 s = laml::normalize(laml::cross(f, up));
            Vector3 u = laml::normalize(laml::cross(s, f));

            laml::identity(result);
            result.c_11 = s.x;
            result.c_21 = s.y;
            result.c_31 = s.z;

            result.c_12 = u.x;
            result.c_22 = u.y;
            result.c_32 = u.z;

            result.c_13 = -f.x;
            result.c_23 = -f.y;
            result.c_33 = -f.z;

            result.c_14 = -laml::dot(s, eye);
            result.c_24 = -laml::dot(u, eye);
            result.c_34 =  laml::dot(f, eye);
            */
        }
    }
}